/*
 * INT_interface.h
 *
 *  Created on: Dec 18, 2020
 *      Author: kh
 */

#ifndef INT_INTERFACE_H_
#define INT_INTERFACE_H_


/*********************************************************************
 *                       MACROS
 *********************************************************************/

/*Interrupts Numbers
 * _____________________________*/
#define EXTINT_0 0		/*INT0*/
#define EXTINT_1 1		/*INT1*/
#define EXTINT_2 2		/*INT2*/

/*Detection State
 * _____________________________*/
#define EXTINT_FALLING_EDGE	 	0  		/*Falling Edge */
#define EXTINT_RISING_EDGE 		1		/*Rising  Edge */
#define EXTINT_ON_CHANGE 		2		/*On Change */
#define EXTINT_LOW_LEVEL 		3		/*Low Level */


/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Initialization
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Copy_u8LevelDetection (Rising or Falling or On Change or Low Level)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8Init(uint8_t Copy_u8ExtIntNo , uint8_t Copy_u8LevelDetection);

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts MCAL_EXTINT_u8Disable
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8Disable(uint8_t Copy_u8ExtIntNo);

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Change Level Detection
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Copy_u8LevelDetection (Rising or Falling or On Change or Low Level)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_u8LevelDetection(uint8_t Copy_u8ExtIntNo , uint8_t Copy_u8LevelDetection);

/*_______________________________________________________________________________________________________________________________*/
/*Description: Interrupts Set Call Back
 * Input     : Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,  Ptr_ToFunction (Pointer To Function To execute in Interrupt)
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_EXTINT_SetCallBack(uint8_t Copy_u8ExtIntNo , void (*Ptr_ToFunction) (void));

#endif /* INT_INTERFACE_H_ */
