/*
 * PWM_software_program.c
 *
 *  Created on: Dec 31, 2020
 *      Author: kh
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"
#include "PWM_software_interface.h"
#include "PWM_software_Cfg.h"

typedef enum
{
	Stop ,
	Start
}PWM_State;

typedef struct
{
	uint8_t PortNo ;
	uint8_t PinNo  ;
	uint8_t TimerChannel ;
	uint16_t TicksNo ;
	uint16_t  DutyCycle ;
	uint16_t On_Time ;
	uint16_t Off_Time ;
	uint16_t counts ;
	PWM_State State ;

}g_PWM_cfg_t;

g_PWM_cfg_t g_PWM_PinArr[ PWM_NUMBER_OF_PINS ] ;

static uint16_t g_u16CompareValue ;

static uint8_t Local_u8Counter ;

static void HAL_PWM_Generate_Timer0(void);
//static void HAL_PWM_Generate_Timer1(void);
//static void HAL_PWM_Generate_Timer2(void);
/*********************************************************************
 *                    FUNCTIONS DEFINTIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: PWM Init
 * Input     : Copy_u8TimerChannel (Timer 0 or 1 or 2) , Copy_u8Prescaler
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t HAL_PWM_SoftwareInit(uint8_t Copy_u8TimerChannel , uint8_t Copy_u8Prescaler , uint16_t Copy_u16CompareValue )
{
	uint8_t Local_u8Error = NO_ERROR ;

	Str_TimerConfiguration_t PWM_cfg = {Copy_u8TimerChannel , Copy_u8Prescaler , TIMER_TIMER_MODE , TIMER_INTERRUPT};

	Local_u8Error = MCAL_Timer_Init(&PWM_cfg);

	g_u16CompareValue = Copy_u16CompareValue ;

	Local_u8Counter = NULL ;

	return Local_u8Error ;
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: PWM Start
 * Input     : Copy_u8Port Port Number , Copy_u8PinNo Pin Number , Copy_u8TimerChannel (Timer 0 or 1 or 2) , Copy_u8SignalTicks , Copy_u16DutyCycleTicks
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t HAL_PWM_SoftwareStart(uint8_t Copy_u8Port , uint8_t Copy_u8PinNo , uint8_t Copy_u8TimerChannel , uint16_t Copy_u8SignalTicks , uint16_t Copy_u16DutyCycleTicks)
{
	uint8_t Local_u8Error = NO_ERROR , Local_u8SearchIndex , Local_u8SearchState = FALSE , Local_u8Loop;

	if(Local_u8Counter <= PWM_NUMBER_OF_PINS)
	{
		for(Local_u8Loop = START_LOOP ; Local_u8Loop < Local_u8Counter && Local_u8SearchState == FALSE ; Local_u8Loop++)
		{
			if( ( g_PWM_PinArr[Local_u8Loop].PortNo == Copy_u8Port )  && (g_PWM_PinArr[Local_u8Loop].PinNo == Copy_u8PinNo) )
			{
				Local_u8SearchState = TRUE ;
				Local_u8SearchIndex = Local_u8Loop ;
			}
		}

		if(Local_u8SearchState == TRUE)
		{
			g_PWM_PinArr[Local_u8SearchIndex].TimerChannel = Copy_u8TimerChannel;
			g_PWM_PinArr[Local_u8SearchIndex].TicksNo = Copy_u8SignalTicks;
			g_PWM_PinArr[Local_u8SearchIndex].DutyCycle = Copy_u16DutyCycleTicks;
			g_PWM_PinArr[Local_u8SearchIndex].counts = NULL ;

			g_PWM_PinArr[Local_u8SearchIndex].On_Time = ((uint16_t)Copy_u16DutyCycleTicks );

			g_PWM_PinArr[Local_u8SearchIndex].Off_Time = g_PWM_PinArr[Local_u8SearchIndex].TicksNo  - g_PWM_PinArr[Local_u8SearchIndex].On_Time ;

			g_PWM_PinArr[Local_u8SearchIndex].State = Start ;

		}
		else
		{

			g_PWM_PinArr[Local_u8Counter].PortNo = Copy_u8Port ;
			g_PWM_PinArr[Local_u8Counter].PinNo = Copy_u8PinNo;
			g_PWM_PinArr[Local_u8Counter].TimerChannel = Copy_u8TimerChannel;
			g_PWM_PinArr[Local_u8Counter].TicksNo = Copy_u8SignalTicks;
			g_PWM_PinArr[Local_u8Counter].DutyCycle = Copy_u16DutyCycleTicks;
			g_PWM_PinArr[Local_u8Counter].counts = NULL ;

			g_PWM_PinArr[Local_u8Counter].On_Time = ((uint16_t)Copy_u16DutyCycleTicks );

			g_PWM_PinArr[Local_u8Counter].Off_Time = g_PWM_PinArr[Local_u8Counter].TicksNo  - g_PWM_PinArr[Local_u8Counter].On_Time ;

			g_PWM_PinArr[Local_u8Counter].State = Start ;

			MCAL_DIO_u8SetPinDir(Copy_u8Port , Copy_u8PinNo  , DIO_OUTPUT);

			Local_u8Counter++;

			if(Local_u8Error == NO_ERROR)
			{
				switch(g_PWM_PinArr[Local_u8Counter].TimerChannel)
				{
					case TIMER0 :
						Local_u8Error = MCAL_TIMER_SetCallBack(g_PWM_PinArr[Local_u8Counter].TimerChannel , HAL_PWM_Generate_Timer0 );

						MCAL_Timer_Start(TIMER0 , g_u16CompareValue);
						break;
					case TIMER1 :
	//					Local_u8Error = MCAL_TIMER_SetCallBack(g_PWM_PinArr[Local_u8Counter].TimerChannel , HAL_PWM_Generate_Timer1 );
						break;
					case TIMER2 :
	//					Local_u8Error = MCAL_TIMER_SetCallBack(g_PWM_PinArr[Local_u8Counter].TimerChannel , HAL_PWM_Generate_Timer2 );
						break;
					default :
						Local_u8Error = ERROR ;
						break;
				}
		}



		}


	}
	else
	{
		Local_u8Error = ERROR ;
	}

	return Local_u8Error ;

}



void HAL_PWM_Generate_Timer0(void)
{
	uint8_t Local_u8Loop ;

	for(Local_u8Loop = START_LOOP ; Local_u8Loop < Local_u8Counter ; Local_u8Loop++)
	{
		if(g_PWM_PinArr[Local_u8Loop].State == Start)
		{
			if(g_PWM_PinArr[Local_u8Loop].TimerChannel == TIMER0)
			{
				if(g_PWM_PinArr[Local_u8Loop].counts == NULL)
				{
					MCAL_DIO_u8SetPinValue(g_PWM_PinArr[Local_u8Loop].PortNo , g_PWM_PinArr[Local_u8Loop].PinNo , DIO_HIGH);
				}
				else if(g_PWM_PinArr[Local_u8Loop].counts == g_PWM_PinArr[Local_u8Loop].On_Time)
				{
					MCAL_DIO_u8SetPinValue(g_PWM_PinArr[Local_u8Loop].PortNo , g_PWM_PinArr[Local_u8Loop].PinNo , DIO_LOW);
				}

				g_PWM_PinArr[Local_u8Loop].counts++ ;

				if(g_PWM_PinArr[Local_u8Loop].counts == g_PWM_PinArr[Local_u8Loop].TicksNo)
				{
					g_PWM_PinArr[Local_u8Loop].counts = NULL ;
				}
			}
		}
	}
}


/*Description: PWM Stop
 * Input     : Copy_u8Port Port Number , Copy_u8PinNo Pin Number
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t HAL_PWM_SoftwareStop(uint8_t Copy_u8Port , uint8_t Copy_u8PinNo )
{
	uint8_t Local_u8Error = NO_ERROR , Local_u8SearchState = FALSE , Local_u8Loop;

	for(Local_u8Loop = START_LOOP ; Local_u8Loop < Local_u8Counter && Local_u8SearchState == FALSE ; Local_u8Loop++)
	{
		if( ( g_PWM_PinArr[Local_u8Loop].PortNo == Copy_u8Port )  && (g_PWM_PinArr[Local_u8Loop].PinNo == Copy_u8PinNo) )
		{
			Local_u8SearchState = TRUE ;
			g_PWM_PinArr[Local_u8Loop].State = Stop;
			MCAL_DIO_u8SetPinValue(g_PWM_PinArr[Local_u8Loop].PortNo , g_PWM_PinArr[Local_u8Loop].PinNo , DIO_LOW);
		}
	}

	if(Local_u8SearchState == FALSE)
	{
		Local_u8Error = ERROR ;
	}

	return Local_u8Error;

}

