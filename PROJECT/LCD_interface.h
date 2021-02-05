/*
 * LCD_interface.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


/*********************************************************************
 *                       MACROS
 *********************************************************************/

/*_____LCD MODE___________________________*/
#define LCD_4_BIT_MODE  4U	/*4 bit Mode*/
#define LCD_8_BIT_MODE  8U  /*8 bit Mode*/

/*_____LCD LINES___________________________*/
#define LCD_LINES_1  	0U   /*1 Line */
#define LCD_LINES_2  	1U   /*2 Lines*/

/*_____LCD FONT___________________________*/
#define LCD_FONT_5_8  	0U   /*5 * 8 Font*/
#define LCD_FONT_5_11  	1U   /*5 * 11 Font*/

/*_____LCD Diplay___________________________*/
#define LCD_DISPLAY_OFF  	0U   /*Display Off*/
#define LCD_DISPLAY_ON  	1U   /*Display On*/

/*_____LCD Cursor___________________________*/
#define LCD_CURSOR_OFF  	0U   /*CURSOR Disable*/
#define LCD_CURSOR_ON	  	1U   /*CURSOR Enable*/

/*_____LCD Cursor blink___________________________*/
#define LCD_CURSOR_BLINK_OFF  		0U   /*CURSOR Blink Disable*/
#define LCD_CURSOR_BLINK_ON		  	1U   /*CURSOR Blink Enable*/


/*********************************************************************
 *                    FUNCTIONS DECLERATIONS
 *********************************************************************/
/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Initialization
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidInit(void);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write Character
 * Input     : Copy_u8Char (Character To Write on LCD)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidWriteCharacter(uint8_t Copy_u8Char);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Write String
 * Input     : ptr_u8String (Pointer to first Character in the String)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidWriteString(uint8_t *ptr_u8String);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Move Cursor
 * Input     : Copy_RowNo (Row Number 0 or 1) , Copy_ColNo (Column No. 0 :15 )
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_MoveCursor(uint8_t Copy_u8RowNo ,  uint8_t Copy_u8ColNo);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Clear All Screen
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidClearAll(void);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Clear Part of Screen
 * Input     : Copy_RowNo (Row Number 0 or 1) Copy_u8Start (Start of column to Clear) , Copy_u8End (End Column To clear)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidClearPart(uint8_t Copy_RowNo , uint8_t Copy_u8Start , uint8_t Copy_u8End);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Display Setup
 * Input     : Copy_u8DisplayValue (Display off or on)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidDisplaySetup(uint8_t Copy_u8DisplayValue);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Cursor Setup
 * Input     : Copy_u8CursorValue (On or Off) , Copy_u8CursorBlink (On or Off)
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_voidWriteNumber(uint32_t Copy_u32Number);

/*_______________________________________________________________________________________________________________________________*/
/*Description: LCD Move Cursor
 * Input     : ptr_Shapes (Pointer to The first Element in special character) , Copy_RowNo (Row Number 0 or 1) , Copy_ColNo (Column No. 0 :15 )
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
extern void HAL_LCD_SpecialChar(uint8_t *ptr_Shapes , uint8_t Copy_RowNo , uint8_t Copy_ColNo);




#endif /* LCD_INTERFACE_H_ */

/*
 * LCD_interface.h
 *
 *  Created on: Dec 12, 2020
 *      Author: kh
 */

//#ifndef LCD_INTERFACE_H_
//#define LCD_INTERFACE_H_
//
//#define BYTES_IN_BLOCK  8U
//
//
//
//extern void HAL_LCD_voidInit(void);
//
//extern void HAL_LCD_voidWriteCharacter(uint8_t Copy_u8Char);
//
//extern void HAL_LCD_voidWriteString(uint8_t *ptr_u8String);
//
//extern void HAL_LCD_MoveCursor(uint8_t Copy_RowNo ,  uint8_t Copy_ColNo);
//
//extern void HAL_LCD_SpecialChar(uint8_t *ptr_Shapes , uint8_t Copy_RowNo , uint8_t Copy_ColNo);
//
//
//
//
//#endif /* LCD_INTERFACE_H_ */
