/*
 * Keypad_interface.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: Initialize Keypad Pins
 * Input     : None
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_KEYPAD_voidInit(void);

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Pressed Key (only one time for each click)
 * Input     : ptr_u8KeyPressed (pointer to Pressed Key )
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_KEYPAD_voidGetKeyOnce(uint8_t * ptr_u8KeyPressed);

/*_______________________________________________________________________________________________________________________________*/
/*Description: Get Pressed Key (Multiple times for each click according to delay )
 * Input     : ptr_u8KeyPressed (pointer to Pressed Key ) , Copy_DelayBetweenClicks_ms (Delay in ms between two clicks to get it again)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_KEYPAD_voidGetKeyMultipe(uint8_t * ptr_u8KeyPressed, uint16_t Copy_DelayBetweenClicks_ms);



#endif /* KEYPAD_INTERFACE_H_ */
