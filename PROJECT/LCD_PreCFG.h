/*
 * LCD_PreCFG.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

#ifndef LCD_PRECFG_H_
#define LCD_PRECFG_H_

/*********************************************************************
 *                       MACROS
 *********************************************************************/
#define LCD_MODE 				LCD_4_BIT_MODE  /*Define LCD Mode 4 Bit Mode or 8 bit Mode*/

/*________________________________________________________*/
/*LCD DATA PINS*/
/*_________________________________________________________*/
#define LCD_DATA_PORT 			DIO_PORTA
#define LCD_DATA_PORT_REG		PORTA
#define LCD_DATA_DIR_REG		DDRA

/*_________________________________________________________
 * LCD CONTROL PINS
 * ________________________________________________________*/
#define LCD_RS_PIN  			DIO_PORTB , DIO_PIN_1   /*Register Select Pin (Command or Data) (Port No , Pin No)*/
#define LCD_RW_PIN  			DIO_PORTB , DIO_PIN_2   /*Read Write Pin (Read or Write) (Port No , Pin No)*/
#define LCD_E_PIN  				DIO_PORTB , DIO_PIN_3   /*Enable Pin (Port No , Pin No)*/

/*_________________________________________________________
 * SPECIAL CHARACTERS CFG
 * ________________________________________________________*/
#define LCD_SPECIAL_BLOCKS  	1U  /*Number of Blocks to Create*/

#define BYTES_IN_BLOCK  		8U  /*Bytes in Each Block*/

#define BLOCKS_BYTES  (LCD_SPECIAL_BLOCKS * BYTES_IN_BLOCK)

/*__________________________________________________________
 * Configurations
 * ________________________________________________________*/
#define LCD_FONT			LCD_FONT_5_11        	/*LCD Font Type*/
#define LCD_LINES			LCD_LINES_2				/*LCD Lines Type*/
#define LCD_CURSOR			LCD_CURSOR_ON			/*LCD Cursor State*/
#define LCD_CURSOR_BLINK	LCD_CURSOR_BLINK_ON		/*LCD Cursor Blink*/

/*********************************************************************
 *                       VARIABLES
 *********************************************************************/
uint8_t arr_Shapes[BLOCKS_BYTES] = {0x00,0x00,0x1F,0x19,0x19,0x19,0x01,0x01}; /*Array to Represent The special Character*/


#endif /* LCD_PRECFG_H_ */

/*
 * LCD_PreCFG.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

//#ifndef LCD_PRECFG_H_
//#define LCD_PRECFG_H_
//
//#define LCD_MODE 4
//
//#define LCD_DATA_PORT DIO_PORTA
//#define LCD_DATA_PORT_REG PORTA
//#define LCD_RS_PIN  DIO_PORTB , DIO_PIN_1
//#define LCD_RW_PIN  DIO_PORTB , DIO_PIN_2
//#define LCD_E_PIN  DIO_PORTB , DIO_PIN_3
//
//#define LCD_SPECIAL_BLOCKS  1
//
//#define BLOCKS_BYTES  (LCD_SPECIAL_BLOCKS * BYTES_IN_BLOCK)
//
//
//#endif /* LCD_PRECFG_H_ */
