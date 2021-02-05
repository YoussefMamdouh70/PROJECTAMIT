/*
 * ICU_program.c
 *
 *  Created on: Jan 22, 2021
 *      Author: kh
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "TIMER_interface.h"
#include "INT_interface.h"
#include "ICU_Cfg.h"
#include "ICU_interface.h"


#define FIRST_STATE		1
#define SECOND_STATE	2
#define THIRD_STATE		3

#define ICU_ONCE	1
#define ICU_MULTI	2

uint8_t g_IcuState ;
uint8_t g_Repeat ;
uint8_t g_EXT_No ;
uint8_t g_TimerChannel ;
void (*Call_BackICU)(uint16_t On_Time , uint16_t Off_Time) = NULL_POINTER ;

static void ICU_Function(void);
/*********************************************************************
 *                    FUNCTIONS DEFINITIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: ICU Initialization
 * Input     : Copy_u8Timer_Channel , Copy_u8Timer_Psc , Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_ICU_voidinit(uint8_t Copy_u8Timer_Channel,  uint8_t Copy_u8Timer_Psc , uint8_t Copy_u8ExtIntNo)
{
	if(Call_BackICU != NULL_POINTER)
	{
		Str_TimerConfiguration_t TimerCfg = {Copy_u8Timer_Channel , Copy_u8Timer_Psc , TIMER_TIMER_MODE , TIMER_POLLING};

		MCAL_Timer_Init(&TimerCfg);

		MCAL_EXTINT_SetCallBack(Copy_u8ExtIntNo , ICU_Function);

		g_EXT_No = Copy_u8ExtIntNo ;
		g_TimerChannel = Copy_u8Timer_Channel ;

	}

}


/*_______________________________________________________________________________________________________________________________*/
/*Description: ICU Value
 * Input     : Pointer To Function ,
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_ICU_voidStartOnce(void (*ptr_IcuValue)(uint16_t On_Time , uint16_t Off_Time))
{
	if(ptr_IcuValue != NULL_POINTER)
	{
		g_Repeat = ICU_ONCE;
		g_IcuState = FIRST_STATE ;
		Call_BackICU = ptr_IcuValue ;

		MCAL_EXTINT_u8Init(g_EXT_No , EXTINT_RISING_EDGE);
	}

}


void ICU_Function(void)
{
	uint8_t On_Time , Off_Time ;

	if(g_Repeat == ICU_ONCE)
	{
		if(g_IcuState == FIRST_STATE)
		{
			g_IcuState = SECOND_STATE ;
			MCAL_EXTINT_u8LevelDetection(g_EXT_No , EXTINT_FALLING_EDGE);
			MCAL_Timer_Start(g_TimerChannel , ICU_TIMER_MAX_COUNT);
		}
		else if(g_IcuState ==SECOND_STATE)
		{
			g_IcuState = THIRD_STATE ;
			MCAL_EXTINT_u8LevelDetection(g_EXT_No , EXTINT_RISING_EDGE);
			MCAL_Timer_Get_Counter(g_TimerChannel , &On_Time );

			MCAL_Timer_Reset(g_TimerChannel);
		}
		else if(g_IcuState ==THIRD_STATE)
		{
			MCAL_Timer_Get_Counter(g_TimerChannel , &Off_Time );

			MCAL_Timer_Stop(g_TimerChannel);

			MCAL_EXTINT_u8Disable(g_EXT_No);

			if(Call_BackICU != NULL_POINTER)
			{
				Call_BackICU(On_Time , Off_Time);
			}
		}
	}
}
