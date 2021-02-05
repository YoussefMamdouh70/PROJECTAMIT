/*
 * LED_interfce.h
 *
 *  Created on: Dec 20, 2020
 *      Author: kh
 */

#ifndef LED_INTERFCE_H_
#define LED_INTERFCE_H_

/*********************************************************************
 *                       MACROS
 *********************************************************************/
#define LED_OFF 	0   /*Led Off*/
#define LED_ON 		1   /*Led On*/

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/

/*_______________________________________________________________________________________________________________________________*/
/*Description: Initialize Pin of LED (Set Direction to Output)
 * Input     : Copy_u8PortNo (Number of Port (PORTA or B or C or D ) , Copy_u8PinNo (Pin No. 0 : 7)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t HAL_LEDInit(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo);

/*_______________________________________________________________________________________________________________________________*/
/*Description: set Led On or Off
 * Input     : Copy_u8PortNo (Number of Port (PORTA or B or C or D ) , Copy_u8PinNo (Pin No. 0 : 7) , Copy_u8LedValue (Led On or Off)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t HAL_LEDSetValue(uint8_t Copy_u8PortNo , uint8_t Copy_u8PinNo , uint8_t Copy_u8LedValue);

#endif /* LED_INTERFCE_H_ */
