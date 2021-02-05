
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"

#include "DIO_interface.h"

#include "Keypad_interface.h"
#include "Keypad_PreCFG.h"
#include "LCD_interface.h"
#include <avr/delay.h>

/*********************************************************************
 *                    VARIABLES
 *********************************************************************/
static uint8_t g_Initcheck ;

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: Initialize Keypad Pins
 * Input     : None
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
void HAL_KEYPAD_voidInit(void)
{
	uint8_t Row_loop, Col_loop;



	for(Col_loop = KEY_COL_START ; Col_loop <= KEY_COL_END ; Col_loop ++)		   /*Initialize The Columns Pins To Output High*/
	{
		MCAL_DIO_u8SetPinDir(KEY_COL_PORT , Col_loop , DIO_OUTPUT);
		MCAL_DIO_u8SetPinValue(KEY_COL_PORT , Col_loop , DIO_HIGH);
	}


	for(Row_loop = KEY_ROW_START ; Row_loop <= KEY_ROW_END ; Row_loop ++)          /*Initialize The Rows pins To Input Pull Up*/
	{
		MCAL_DIO_u8SetPinDir(KEY_ROW_PORT , Row_loop , DIO_INPUT);
		MCAL_DIO_u8SetPinInputType(KEY_ROW_PORT , Row_loop , DIO_INPUT_PULL_UP);
	}

	HAL_LCD_voidInit();

	g_Initcheck = NO_ERROR ;
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Pressed Key (only one time for each click)
 * Input     : ptr_u8KeyPressed (pointer to Pressed Key )
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
void HAL_KEYPAD_voidGetKeyOnce(uint8_t * ptr_u8KeyPressed)
{
	uint8_t Row_loop, Col_loop , Key_Pressed = DIO_HIGH;

	if(g_Initcheck == NO_ERROR) /*Check if Module is Initialized*/
	{
		for(Col_loop = KEY_COL_START ; Col_loop <= KEY_COL_END ; Col_loop++)
		{
			MCAL_DIO_u8SetPinValue(KEY_COL_PORT , Col_loop , DIO_LOW);   /*set Column To Low to Check if The key is Pressed in this Column*/

			for(Row_loop = KEY_ROW_START ; Row_loop <= KEY_ROW_END ; Row_loop++)
			{
				MCAL_DIO_u8GetPinValue(KEY_ROW_PORT , Row_loop , &Key_Pressed); /*Read The Row if The Column is Pressed Then we will read Low*/

				if(Key_Pressed == DIO_LOW)
				{
					*ptr_u8KeyPressed = Key_Matrix[Col_loop - KEY_COL_START][Row_loop - KEY_ROW_START]; /*Get The Pressed Key to return it*/

					while(Key_Pressed == DIO_LOW)
					{
						MCAL_DIO_u8GetPinValue(KEY_ROW_PORT , Row_loop , &Key_Pressed);  /*Block on the Key*/
					}
				}
			}

			MCAL_DIO_u8SetPinValue(KEY_COL_PORT , Col_loop , DIO_HIGH);  /*Set The column to High to look for another Column*/
		}
	}

}

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Pressed Key (Multiple times for each click according to delay )
 * Input     : ptr_u8KeyPressed (pointer to Pressed Key ) , Copy_DelayBetweenClicks_ms (Delay in ms between two clicks to get it again)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
void HAL_KEYPAD_voidGetKeyMultipe(uint8_t * ptr_u8KeyPressed, uint16_t Copy_DelayBetweenClicks_ms)
{
	uint8_t Row_loop, Col_loop , Key_Pressed = DIO_HIGH;

	if(g_Initcheck == NO_ERROR) /*Check if Module is Initialized*/
	{
		for(Col_loop = KEY_COL_START ; Col_loop <= KEY_COL_END ; Col_loop ++)
		{
			MCAL_DIO_u8SetPinValue(KEY_COL_PORT , Col_loop , DIO_LOW);   /*set Column To Low to Check if The key is Pressed in this Column*/

			for(Row_loop = KEY_ROW_START ; Row_loop <= KEY_ROW_END ; Row_loop ++)
			{
				MCAL_DIO_u8GetPinValue(KEY_ROW_PORT , Row_loop , &Key_Pressed); /*Read The Row if The Column is Pressed Then we will read Low*/

				if(Key_Pressed == DIO_LOW)
				{
					*ptr_u8KeyPressed = Key_Matrix[Row_loop - KEY_ROW_START][Col_loop - KEY_COL_START]; /*Get The Pressed Key to return it*/

					_delay_ms(Copy_DelayBetweenClicks_ms);
				}
			}

			MCAL_DIO_u8SetPinValue(KEY_COL_PORT , Col_loop , DIO_HIGH);  /*Set The column to High to look for another Column*/
		}
	}

}
