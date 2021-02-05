/*
 * ICU_interface.h
 *
 *  Created on: Jan 22, 2021
 *      Author: kh
 */

#ifndef ICU_INTERFACE_H_
#define ICU_INTERFACE_H_

/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: ICU Initialization
 * Input     : Copy_u8Timer_Channel , Copy_u8Timer_Psc , Copy_u8ExtIntNo (Interrupt Number INT 0 or 1 or 2) ,
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_ICU_voidinit(uint8_t Copy_u8Timer_Channel,  uint8_t Copy_u8Timer_Psc , uint8_t Copy_u8ExtIntNo);


/*_______________________________________________________________________________________________________________________________*/
/*Description: ICU Value
 * Input     : Pointer To Function ,
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void HAL_ICU_voidStartOnce(void (*ptr_IcuValue)(uint16_t On_Time , uint16_t Off_Time));

#endif /* ICU_INTERFACE_H_ */
