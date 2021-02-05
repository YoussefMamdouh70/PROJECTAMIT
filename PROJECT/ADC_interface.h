/*
 * ADC_interface.h
 *
 *  Created on: Dec 19, 2020
 *      Author: kh
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*________________________________________________________________*/
/******************************************************************/
/*                        MACROS                                  */
/******************************************************************/

#define ADC_DIO_PORT									DIO_PORTA


/*________ADC Channel Selection_______*/

#define ADC_CHANNEL0 									0U			/*Channel 0*/
#define ADC_CHANNEL1 									1U			/*Channel 1*/
#define ADC_CHANNEL2 									2U			/*Channel 2*/
#define ADC_CHANNEL3 									3U			/*Channel 3*/
#define ADC_CHANNEL4 									4U			/*Channel 4*/
#define ADC_CHANNEL5 									5U			/*Channel 5*/
#define ADC_CHANNEL6 									6U			/*Channel 6*/
#define ADC_CHANNEL7 									7U			/*Channel 7*/
/*________________________________________________________________________________________________*/



/*_______Vref Selection__________________*/

#define ADC_AREF_INTERNAL_VREF_OFF                    	0U			/*In Case of  AREF*/
#define ADC_AVCC_WITH_EXTERNAL_CAPACITOR_AT_VREF 		1U			/*In Case of AVCC*/
#define ADC_INTERNAL_2_56_VREF                   		2U			/*In Case of Internal 2.56 v*/
/*_______________________________________________________________________________________________*/



/*________ADC Mode Interrut or Polling __*/

#define ADC_INTRRUPT 									1U			/*In Case Of Interrupt*/
#define ADC_POLLING  									2U			/*In Case of Polling*/

/*_________________________________________________________________________________________________*/




/*________Data Adjustment_________________*/

#define ADC_RIGHT_ADJUST 								0U			/*In Case of Right Adjustment*/
#define ADC_LEFT_ADJUST  								1U			/*In Case of Left Adjustment*/

/*__________________________________________________________________________________________________*/

/*_________Auto Trigger Source_____________*/
#define ADC_NO_AUTO_TRIGGER				  				8U			/*Disable Auto Trigger*/
#define ADC_FREE_RUNNING_MODE             				0U			/*Free Running Mode*/
#define ADC_ANALOGE_COMPARETOR            				1U			/*Analog Comparator*/
#define ADC_EXTERNAL_INTERRUPT0_REQUEST   				2U			/*Trigger INT0*/
#define ADC_TIMER0_COMPARE_MATCH          				3U			/*Trigger when Compare Match occur*/
#define ADC_TIMER0_OVER_FLOW              				4U			/*Trigger When Overflow Occur*/
#define ADC_TIMER1_COMPARE_MATCH          				5U          /*Trigger when Compare Match occur*/
#define ADC_TIMER1_OVER_FLOW              				6U          /*Trigger When Overflow Occur*/
#define ADC_TIMER1_CAPTURE_EVENT          				7U			/*capture Event*/

/*__________________________________________________________________________________________________*/

/*________ADC Prescaller Selection_________*/

#define ADC_PRESCALLER_2    							1U			/*Division Factor of 2*/
#define ADC_PRESCALLER_4    							2U			/*Division Factor of 4*/
#define ADC_PRESCALLER_8    							3U			/*Division Factor of 8*/
#define ADC_PRESCALLER_16   							4U			/*Division Factor of 16*/
#define ADC_PRESCALLER_32   							5U			/*Division Factor of 32*/
#define ADC_PRESCALLER_64   							6U			/*Division Factor of 64*/
#define ADC_PRESCALLER_128  							7U			/*Division Factor of 128*/

/*___________________________________________________________________________________________________*/


/*_______ADC Channel Type___________________*/

#define ADC_SINGLE_ENDED_INPUT 							0U			/*Single Ended Mode*/
#define ADC_POSITIVE_DIFFRENTIAL_INPUT 					1U			/*Differential Mode*/
#define ADC_NEGATIVE_DIFFRENTIAL_INPUT 					2U


/*____________________________________________________________________________________________________*/


/*________________________________________________________________*/
/******************************************************************/
/*                    Struct Function Input                       */
/******************************************************************/
typedef struct
{
	uint8_t u8REF_Select;
	uint8_t u8InterruptOrPolling;
	uint8_t u8DataAdustment;
	uint8_t u8AutoTriggerSource;
	uint8_t u8Prescaller;

}ADC_ConfigStr_t;


/*________________________________________________________________*/
/******************************************************************/
/*                        FUNCTIONS PROTOTYPES                    */
/******************************************************************/


/*_______________________________________________________________________________________________________________________________*/
/*Description: ADC Initialization
 * Input     : Timer_Configuration_S* Confg_S (Struct contain : Ref Select,Interrupt Mode, Adjustment left or right , Auto Trigger , Prescaller as described in Struct)
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t MCAL_ADC_Init(ADC_ConfigStr_t * ADC_ConfigSt);

/*_______________________________________________________________________________________________________________________________*/
/*Description: ADC Start Conversion
 * Input     : ADC Channel , ADC Channel Type, pointer to receive the value of conversion
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t MCAL_ADC_StartCoversionBusyWait(uint8_t u8ADC_Channel , uint16_t *ptr_Result);

/*_______________________________________________________________________________________________________________________________*/
/*Description: ADC Start Conversion
 * Input     : ADC Channel , ADC Channel Type, pointer to Function with parameter to use value of Conversion
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
extern uint8_t MCAL_ADC_StartCoversionSetCallBackISR(uint8_t u8ADC_Channel , void (*Ptr_FunctionADC)(uint16_t Copy_u16Result));


#endif /* ADC_INTERFACE_H_ */
