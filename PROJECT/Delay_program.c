/*
 * Delay_program.c
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "TIMER_interface.h"
#include "Delay_interface.h"
#include "Delay_Cfg.h"


static uint8_t g_u8TimerChannel ;
/*_______________________________________________________________________________________________________________________________*/
/*Description: Delay Initialization
 * Input     : Timer_Channel ( 0 or 1 or 2)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_DelayInit(uint8_t Copy_u8TimerChannel)
{
	g_u8TimerChannel = Copy_u8TimerChannel ;

	Str_TimerConfiguration_t Delay_Cfg = {Copy_u8TimerChannel ,  DELAY_PRESCALLER , TIMER_TIMER_MODE , TIMER_POLLING};

	MCAL_Timer_Init(&Delay_Cfg);
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Delay wait
 * Input     : Delay in ms
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_DelayBusyWait_ms(uint16_t Copy_u16Delay_ms)
{

	uint8_t Local_u8FlagStatus = DISABLE;

	while(Copy_u16Delay_ms != DISABLE)
	{
		Local_u8FlagStatus = DISABLE ;

		MCAL_Timer_Start(g_u8TimerChannel, DELAY_TICK);

		MCAL_Timer_Get_FlagStatus(g_u8TimerChannel , &Local_u8FlagStatus);

		while(Local_u8FlagStatus != ENABLE)
		{
			MCAL_Timer_Get_FlagStatus(g_u8TimerChannel , &Local_u8FlagStatus);
		}

		MCAL_Timer_Clear_FlagStatus(g_u8TimerChannel);

		Copy_u16Delay_ms-- ;
	}
}
