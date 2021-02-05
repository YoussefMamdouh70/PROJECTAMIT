/*
 * INT_program.c
 *
 *  Created on: Dec 18, 2020
 *      Author: kh
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "AVR_INT_REG.h"
#include "INT_interface.h"
#include "DIO_interface.h"

/*********************************************************************
 *                    VARIABLES
 *********************************************************************/
void (*g_PtrCallBack_INT0)(void) = NULL_POINTER;			/*Pointer To Function of INT0*/
void (*g_PtrCallBack_INT1)(void) = NULL_POINTER;			/*Pointer To Function of INT1*/
void (*g_PtrCallBack_INT2)(void) = NULL_POINTER;			/*Pointer To Function of INT2*/

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT0
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_1(void)__attribute((signal,used));			/*ISR Function of INT0*/
/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT1
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_2(void)__attribute((signal,used));			/*ISR Function of INT1*/
/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT1
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_3(void)__attribute((signal,used));			/*ISR Function of INT2*/

/*********************************************************************
 *                    FUNCTIONS DEFINITIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Initialization
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Copy_u8LevelDetection (Rising or Falling or On Change or Low Level)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8Init(uint8_t Copy_u8ExtIntNo , uint8_t Copy_u8LevelDetection)
{
	uint8_t Local_Error_Statue = NO_ERROR ;

	switch(Copy_u8ExtIntNo)											/*Check if entered INT No. is Available */
	{
		case EXTINT_0 :
			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);

			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);

			}
			else if(Copy_u8LevelDetection == EXTINT_ON_CHANGE)			/*In Case Of On Change*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);

			}
			else if(Copy_u8LevelDetection == EXTINT_LOW_LEVEL)			/*In Case Of Low Level*/
			{
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);
			}
			else
			{
				Local_Error_Statue = ERROR;								/*Error Status : Error*/
			}

			if(Local_Error_Statue == NO_ERROR)
			{

				SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);					/*Enable Global Interrupt*/

				SET_BIT(EXTINT_GICR , GICR_INT_0);							/*Enable INT 0*/
			}

			break ;

		case EXTINT_1 :

			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);

			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);

			}
			else if(Copy_u8LevelDetection == EXTINT_ON_CHANGE)			/*In Case Of On Change*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);

			}
			else if(Copy_u8LevelDetection == EXTINT_LOW_LEVEL)			/*In Case Of Low Level*/
			{
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);
			}
			else
			{
				Local_Error_Statue = ERROR;								/*Error Status : Error*/
			}

			if(Local_Error_Statue == NO_ERROR)
			{

				SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);					/*Enable Global Interrupt*/

				SET_BIT(EXTINT_GICR , GICR_INT_1);							/*Enable INT 1*/
			}

			break ;

		case EXTINT_2 :
			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUSCR , MCUSCR_ISC2);
			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				CLR_BIT(EXTINT_MCUSCR , MCUSCR_ISC2);
			}
			else
			{
				Local_Error_Statue = ERROR ;
			}

			if(Local_Error_Statue == NO_ERROR)
			{

				SET_BIT(EXTINT_SREG , SREG_GLOBAL_ENABLE);					/*Enable Global Interrupt*/

				SET_BIT(EXTINT_GICR , GICR_INT_2);							/*Enable INT 2*/
			}

			break ;
		default :
			Local_Error_Statue = ERROR ;

	}

	return Local_Error_Statue ;
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts MCAL_EXTINT_u8Disable
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8Disable(uint8_t Copy_u8ExtIntNo)
{

	uint8_t Local_Error_Statue = NO_ERROR ;

	switch(Copy_u8ExtIntNo)											/*Check if entered INT No. is Available */
	{
		case EXTINT_0 :
			CLR_BIT(EXTINT_GICR , GICR_INT_0);
			break ;
		case EXTINT_1 :
			CLR_BIT(EXTINT_GICR , GICR_INT_1);
			break ;
		case EXTINT_2 :
			CLR_BIT(EXTINT_GICR , GICR_INT_2);
			break ;
		default :
			Local_Error_Statue = ERROR ;
			break ;

	}

	return Local_Error_Statue ;

}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Change Level Detection
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Copy_u8LevelDetection (Rising or Falling or On Change or Low Level)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8LevelDetection(uint8_t Copy_u8ExtIntNo , uint8_t Copy_u8LevelDetection)
{
	uint8_t Local_Error_Statue = NO_ERROR ;

    switch(Copy_u8ExtIntNo)											/*Check if entered INT No. is Available */
	{
		case EXTINT_0 :
			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);

			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC01);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);

			}
			else if(Copy_u8LevelDetection == EXTINT_ON_CHANGE)			/*In Case Of On Change*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);

			}
			else if(Copy_u8LevelDetection == EXTINT_LOW_LEVEL)			/*In Case Of Low Level*/
			{
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC00);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC01);
			}
			else
			{
				Local_Error_Statue = ERROR;								/*Error Status : Error*/
			}

			break ;

		case EXTINT_1 :

			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);

			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC11);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);

			}
			else if(Copy_u8LevelDetection == EXTINT_ON_CHANGE)			/*In Case Of On Change*/
			{
				SET_BIT(EXTINT_MCUCR , MCUCR_ISC10);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);

			}
			else if(Copy_u8LevelDetection == EXTINT_LOW_LEVEL)			/*In Case Of Low Level*/
			{
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC10);
				CLR_BIT(EXTINT_MCUCR , MCUCR_ISC11);
			}
			else
			{
				Local_Error_Statue = ERROR;								/*Error Status : Error*/
			}

			break ;

		case EXTINT_2 :
			if(Copy_u8LevelDetection == EXTINT_RISING_EDGE)				/*In Case Of Rising Edge*/
			{
				SET_BIT(EXTINT_MCUSCR , MCUSCR_ISC2);
			}
			else if(Copy_u8LevelDetection == EXTINT_FALLING_EDGE)		/*In Case Of Falling Edge*/
			{
				CLR_BIT(EXTINT_MCUSCR , MCUSCR_ISC2);
			}
			else
			{
				Local_Error_Statue = ERROR ;
			}

			break ;
		default :
			Local_Error_Statue = ERROR ;

	}

	return Local_Error_Statue ;

}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Set Call Back
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Ptr_ToFunction (Pointer To Function To execute in Interrupt)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_SetCallBack(uint8_t Copy_u8ExtIntNo , void (*Ptr_ToFunction) (void))
{
	uint8_t Local_Error_Statue = NO_ERROR;

	switch(Copy_u8ExtIntNo)
	{
		case EXTINT_0 :
			g_PtrCallBack_INT0 = Ptr_ToFunction ;    	/*Pointer to Function to send to ISR*/
			break;
		case EXTINT_1 :
			g_PtrCallBack_INT1 = Ptr_ToFunction ;		/*Pointer to Function to send to ISR*/
			break;
		case EXTINT_2 :
			g_PtrCallBack_INT2 = Ptr_ToFunction ;		/*Pointer to Function to send to ISR*/
			break;
		default :
			Local_Error_Statue = ERROR;
			break ;
	}

	return Local_Error_Statue ;
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT0
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_1(void)
{
	if(g_PtrCallBack_INT0 != NULL) 		/*Check that Pointer is not Pointing to NULL */
	{
		g_PtrCallBack_INT0();			/*Execute Function*/
	}
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT1
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_2(void)
{
	if(g_PtrCallBack_INT1 != NULL)		/*Check that Pointer is not Pointing to NULL */
	{
		g_PtrCallBack_INT1();           /*Execute Function*/
	}

}

/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of INT2
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_3(void)
{
	if(g_PtrCallBack_INT2 != NULL)		/*Check that Pointer is not Pointing to NULL */
	{
		g_PtrCallBack_INT2();           /*Execute Function*/
	}

}
