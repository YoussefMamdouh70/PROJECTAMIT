/*
 * Keypad_PreCFG.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

#ifndef KEYPAD_PRECFG_H_
#define KEYPAD_PRECFG_H_


/*********************************************************************
 *                   MACROS
 *********************************************************************/

#define KEY_ROW_PORT  DIO_PORTC   /*Define Port of The Rows*/
#define KEY_COL_PORT  DIO_PORTC   /*Define Port of The Columns*/


#define KEY_ROW_START DIO_PIN_4   /*define Start Pin of Rows*/
#define KEY_ROW_END DIO_PIN_7     /*define End Pin of Rows*/

#define KEY_COL_START DIO_PIN_0   /*define Start Pin of Columns*/
#define KEY_COL_END DIO_PIN_3     /*define end Pin of Columns*/


/*********************************************************************
 *                   VARIABLES
 *********************************************************************/
uint8_t Key_Matrix[KEY_ROW_END - KEY_ROW_START + 1][KEY_COL_END - KEY_COL_START + 1 ]= {{'1','2','3','5'},{'4','5','6','5'},{'7','8','9','5'}};  /*Array that represent Keys*/

#endif /* KEYPAD_PRECFG_H_ */
