/*
 * Delay_interface.h
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */

#ifndef DELAY_INTERFACE_H_
#define DELAY_INTERFACE_H_


/*_______________________________________________________________________________________________________________________________*/
/*Description: Delay Initialization
 * Input     : Timer_Channel ( 0 or 1 or 2)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_DelayInit(uint8_t Copy_u8TimerChannel);


/*_______________________________________________________________________________________________________________________________*/
/*Description: Delay wait
 * Input     : Delay in ms
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_DelayBusyWait_ms(uint16_t Copy_u16Delay_ms);
#endif /* DELAY_INTERFACE_H_ */
