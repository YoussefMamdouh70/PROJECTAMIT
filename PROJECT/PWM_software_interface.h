/*
 * PWM_software_interface.h
 *
 *  Created on: Dec 31, 2020
 *      Author: kh
 */

#ifndef PWM_SOFTWARE_INTERFACE_H_
#define PWM_SOFTWARE_INTERFACE_H_


/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: PWM Init
 * Input     : Copy_u8TimerChannel (Timer 0 or 1 or 2) , Copy_u8Prescaler , Copy_u16CompareValue CTC Value
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t HAL_PWM_SoftwareInit(uint8_t Copy_u8TimerChannel , uint8_t Copy_u8Prescaler , uint16_t Copy_u16CompareValue );


/*_______________________________________________________________________________________________________________________________*/
/*Description: PWM Start
 * Input     : Copy_u8Port Port Number , Copy_u8PinNo Pin Number , Copy_u8TimerChannel (Timer 0 or 1 or 2) , Copy_u8SignalTicks , Copy_u8DutyCycleTicks
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t HAL_PWM_SoftwareStart(uint8_t Copy_u8Port , uint8_t Copy_u8PinNo , uint8_t Copy_u8TimerChannel , uint16_t Copy_u8SignalTicks , uint16_t Copy_u16DutyCycleTicks);

/*Description: PWM Stop
 * Input     : Copy_u8Port Port Number , Copy_u8PinNo Pin Number
 * Output    : Error Status
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t HAL_PWM_SoftwareStop(uint8_t Copy_u8Port , uint8_t Copy_u8PinNo );

#endif /* PWM_SOFTWARE_INTERFACE_H_ */
