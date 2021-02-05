/*
 * LED_program.c
 *
 *  Created on: Dec 20, 2020
 *      Author: kh
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"

#include "LED_interfce.h"

#include "DIO_interface.h"

/*********************************************************************
 *                    VARIABLES
 *********************************************************************/
static uint8_t g_Initcheck ;


/*********************************************************************
 *                    FUNCTIONS DEFINITIONS
 *********************************************************************/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Initialize Pin of LED (Set Direction to Output)
 * Input     : Copy_u8PortNo (Number of Port (PORTA or B or C or D ) , Copy_u8PinNo (Pin No. 0 : 7)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t HAL_LEDInit(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo)
{
	uint8_t Local_u8Error = NO_ERROR;  													/*Error Status : No Error*/

	Local_u8Error = MCAL_DIO_u8SetPinDir(Copy_u8PortNo , Copy_u8PinNo , DIO_OUTPUT); 	/*Set Pin To Output*/

	g_Initcheck = NO_ERROR ; /*Module is Initialized*/

	return Local_u8Error ; 																/*return Error*/
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: set Led On or Off
 * Input     : Copy_u8PortNo (Number of Port (PORTA or B or C or D ) , Copy_u8PinNo (Pin No. 0 : 7) , Copy_u8LedValue (Led On or Off)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t HAL_LEDSetValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8LedValue)
{
	uint8_t Local_u8Error = NO_ERROR;  													/*Error Status : No Error*/

	if(g_Initcheck == NO_ERROR)  /*Check if Module is Initialized*/
	{
		Local_u8Error = MCAL_DIO_u8SetPinValue(Copy_u8PortNo , Copy_u8PinNo , Copy_u8LedValue); 	/*Set Pin To Output*/
	}
	else
	{
		Local_u8Error = ERROR ;
	}

	return Local_u8Error ; 																/*return Error*/
}


