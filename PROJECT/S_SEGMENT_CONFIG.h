/*
 * S_SEGMENT_CONFIG.h
 *
 * Created: 12/11/2020 5:15:09 PM
 *  Author: Amrha
 */ 


#ifndef S_SEGMENT_CONFIG_H_
#define S_SEGMENT_CONFIG_H_

#include "DIO_interface.h"

#define S_SEGMENT_ENABLE_2 DIO_PORTB ,DIO_PIN_1
#define S_SEGMENT_ENABLE_1 DIO_PORTB ,DIO_PIN_2

#define S_SEGMENT_DOT DIO_PORTB ,DIO_PIN_3

#define S_SEGMENT_A DIO_PORTA ,DIO_PIN_4
#define S_SEGMENT_B DIO_PORTA ,DIO_PIN_5
#define S_SEGMENT_C DIO_PORTA ,DIO_PIN_6
#define S_SEGMENT_D DIO_PORTA ,DIO_PIN_7

#endif /* S_SEGMENT_CONFIG_H_ */
