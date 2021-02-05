/*
 * TIMER_program.c
 *
 *  Created on: Dec 26, 2020
 *      Author: kh
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "AVR_TIMER_REG.h"
#include "DIO_interface.h"
#include "TIMER_interface.h"



#define CLR_PRE_SCALLER 	0xf8
#define RESET_COUNTER 		0U

/*________________________________________________________________*/
/******************************************************************/
/*                        GLOBAL VARIABLES                        */
/******************************************************************/

void __vector_10(void)__attribute((signal,used));

static void (*TIMER0_CallBack)(void)=0;
//*******************************************************************************************


static uint8_t GSA_uint8_Prescaler_Timer[NO_OF_CHANNELS];  /*Array to Copy Pre-scaler for each Timer Channel from Initialization  to Start*/
/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Initialization
 * Input     : Timer_Configuration_S* Confg_S (Struct contain : Timer Channel, Prescaler, Timer mode , Mode as described in Struct)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Init(Str_TimerConfiguration_t* Confg_S)
{
	uint8_t Local_u8Error = NO_ERROR ;

	switch(Confg_S->Timer_Channel)                /*Check Timer Channel (Timer0 , Timer1, Timer2)*/
	{
		case TIMER0:                              /*In case Timer0*/
			/*_______________________Check Timer Mode________________________________________________________________*/
			switch(Confg_S -> Timer_Mode)         /*Check if Selected Mode is Counter or Timer*/
			{
				case TIMER_TIMER_MODE :case TIMER_COUNTER_MODE :
					GSA_uint8_Prescaler_Timer[TIMER0] = Confg_S ->Timer_Psc;  /*Set Pre-scaler to send it To Start Function*/
					break;
				default :
					Local_u8Error = ERROR;  /*Return Error*/
					break;
			}
			/*________________________________________________________________________________________________________*/

			/*_____________________Check OverFlow Mode________________________________________________________________*/
			if(Local_u8Error == NO_ERROR)          /*Check If Chosen OverFlow mode is Polling or Interrupt*/
			{
				if(Confg_S->Interrupt_Mode == TIMER_INTERRUPT)
				{
					SET_BIT(STATUS_REGISTER,GLOBAL_INTERRUPT_BIT);   /*Enable Global Interrupt*/
					SET_BIT(TIMER0_INTERRUPT_MASK_REGISTER , TIMER0_INTERRUPT_COMPARE_MATCH_ENABLE_BIT);
				}
				else if(Confg_S->Interrupt_Mode == TIMER_POLLING)
				{
					CLR_BIT(TIMER0_INTERRUPT_MASK_REGISTER , TIMER0_INTERRUPT_COMPARE_MATCH_ENABLE_BIT);
				}
				else
				{
					Local_u8Error = ERROR ;
				}
			}
			/*__________________________________________________________________________________________________________*/

			SET_BIT(TIMER0_CONTROL_REGISTER , TIMER0_CONTROL_WAVEGENERATION_1);
			CLR_BIT(TIMER0_CONTROL_REGISTER , TIMER0_CONTROL_WAVEGENERATION_0);

			break;
		default :
			Local_u8Error = ERROR;
			break;
	}
	return Local_u8Error ;
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Start
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), Tick Counting (Counts given by user)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Start(uint8_t Copy_uint8_TimerChannel,uint32_t Copy_uint32_TickCounts)
{

	uint8_t Local_u8Error = NO_ERROR;

	switch(Copy_uint8_TimerChannel)
		{
		case TIMER0 :
			if(Copy_uint32_TickCounts  <= TIMER0_OVERFLOW)
			{
				//TIMER0_COUNTER_REGISTER = TIMER0_OVERFLOW  - Copy_uint32_TickCounts;

				TIMER0_OUTPUT_COMPARE_MATCH = Copy_uint32_TickCounts ;

				TIMER0_CONTROL_REGISTER = (TIMER0_CONTROL_REGISTER & CLR_PRE_SCALLER) | GSA_uint8_Prescaler_Timer[TIMER0];
			}
			else
			{
				Local_u8Error= ERROR;
			}
			break;
		default :
			Local_u8Error = ERROR;
			break;

		}
	return Local_u8Error;
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer/Counter Stop
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Stop(uint8_t Copy_uint8_TimerChannel)
{
	uint8_t Local_uint8_ErrorStatus = NO_ERROR; /*Error Status : No Error*/

	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			TIMER0_CONTROL_REGISTER &= (uint8_t) CLR_PRE_SCALLER; /*Stop Pre Scaler*/
			break;

		default:
			Local_uint8_ErrorStatus = ERROR; /*Error Status : Error*/
			break;

	}

	return Local_uint8_ErrorStatus; /*Return Error Status*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer Reset
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Reset(uint8_t Copy_uint8_TimerChannel)
{
	uint8_t Local_uint8_ErrorStatus = NO_ERROR;  /*Error Status : No Error*/

	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			TIMER0_COUNTER_REGISTER = RESET_COUNTER; /*Reset Counter */
			break;
		default:
			Local_uint8_ErrorStatus = ERROR; /*Error Status : Error*/
			break;

	}

	return Local_uint8_ErrorStatus; /*Return Error Status*/
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Count
 * Input     :  Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Get_Counter(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_TimerCounter)
{
	uint8_t Local_uint8_ErrorStatus = NO_ERROR;  /*Error Status : No Error*/

		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0 :
				*Copy_uint8Ptr_TimerCounter = TIMER0_COUNTER_REGISTER;
				break;
			default:
				Local_uint8_ErrorStatus = ERROR; /*Error Status : Error*/
				break;
		}


	return Local_uint8_ErrorStatus;
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Timer Tick Time value to use it by user
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *Timer_Time (Pointer to return Value)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
 uint8_t MCAL_Timer_Get_TickTime(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_TimerTickTime)
{
	uint8_t Local_uint8_ErrorStatus = NO_ERROR;  /*Error Status :No Error*/

	if(Copy_uint8Ptr_TimerTickTime == NULL_POINTER)
	{
		Local_uint8_ErrorStatus = ERROR;   /*Error Status : Error*/
	}
	else
	{
		switch(Copy_uint8_TimerChannel)
		{
			case TIMER0 :
				if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_SYSTEM_CLOCK_US;   /*Pre Scaler = System Clock*/
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_8_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_8_US;   /*Pre Scaler = System Clock/8 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_64_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_64_US;   /*Pre Scaler = System Clock/64 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_256_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_256_US;   /*Pre Scaler = System Clock/256 */
				}
				else if(GSA_uint8_Prescaler_Timer[TIMER0] == F_CPU_CLOCK_1024_TIMER_0)
				{
					*Copy_uint8Ptr_TimerTickTime = TICKTIME_1024_US;   /*Pre Scaler = System Clock/1024 */
				}
				else
				{
					Local_uint8_ErrorStatus = ERROR;   /*Error Status : Error*/
				}
				break;
			default:
				Local_uint8_ErrorStatus = ERROR;     /*Error Status : Error*/
				break;
		}
	}

		return Local_uint8_ErrorStatus; /*Return Error Status*/
}


 /*_______________________________________________________________________________________________________________________________*/
 /*Description: Get Timer Flag Status
  * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
  * Output    : Error Checking
  *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Get_FlagStatus(uint8_t Copy_uint8_TimerChannel, uint8_t *Copy_uint8Ptr_FlagStatus)
 {
 	uint8_t Local_uint8_ErrorStatus = NO_ERROR;        /*Error status : No Error */

 	if(Copy_uint8Ptr_FlagStatus == NULL_POINTER)       /*Check if pointer points to NULL*/
 	{
 		Local_uint8_ErrorStatus = ERROR;
 	}
 	switch(Copy_uint8_TimerChannel)
 	{
 		case TIMER0 :
 			/**Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_OVERFLOW_FLAG_BIT);*/ /*Read Flag*/
 			*Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_COMPARE_MATCH_FLAG_BIT);
 			break;
 		default:
 			Local_uint8_ErrorStatus = ERROR;  /*Error status : Error */
 			break;
 	}

 	return Local_uint8_ErrorStatus;  /*Return Error*/
 }

/*_______________________________________________________________________________________________________________________________*/
/*Description: Clear Timer Flag Status
 * Input     : Timer Channel(Timer Channel (Timer0 or Timer1 or Timer2), *FlagStatus (Pointer to Flag)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_Timer_Clear_FlagStatus(uint8_t Copy_uint8_TimerChannel)
{
	uint8_t Local_uint8_ErrorStatus = NO_ERROR;        /*Error status : No Error */

	switch(Copy_uint8_TimerChannel)
	{
		case TIMER0 :
			/**Copy_uint8Ptr_FlagStatus = GET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_OVERFLOW_FLAG_BIT);*/ /*Read Flag*/
			SET_BIT(TIMER0_INTERRUPT_FLAG_REGISTER,TIMER0_INTERRUPT_COMPARE_MATCH_FLAG_BIT);
			break;
		default:
			Local_uint8_ErrorStatus = ERROR;  /*Error status : Error */
			break;
	}

	return Local_uint8_ErrorStatus;  /*Return Error*/
}
/*_______________________________________________________________________________________________________________________________*/
/*Description: Set Call Back
 * Input     : Copy_uint8_TimerChannel , Copy_FunctionAddress
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_TIMER_SetCallBack(uint8_t Copy_uint8_TimerChannel,void (*Copy_FunctionAddress)(void))
{
	uint8_t Local_u8ErrorState= NO_ERROR;              //Error State: No Error

	if(Copy_FunctionAddress==NULL_POINTER) //check if pointer points to Nothing
	{
		Local_u8ErrorState=1;             //Error State : Error
	}
	else
	{
		switch(Copy_uint8_TimerChannel)                   //Switch on INT
		{
			case TIMER0 :                                 //In Case INT0
				TIMER0_CallBack =Copy_FunctionAddress;//Send Function Address To Call Back pointer
				break;
			default :
				Local_u8ErrorState= ERROR;  //Error State : Error
				break;

		}
	}
	return Local_u8ErrorState; //Return Error State
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Timer 0 ISR Compare Match
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_10(void)
{
	if(TIMER0_CallBack!=0)
	{
		TIMER0_CallBack();
	}
}
