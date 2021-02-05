/*
 * ADC_program.c
 *
 *  Created on: Dec 19, 2020
 *      Author: kh
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "AVR_ADC_REG.h"

#define LAST_3_BITS_SHIFT		5

#define LAST_3_BITS_CLEAR		0x1F

#define FIRST_5_BITS_CLEAR		0xE0

#define SHIT_6_BITS		6
#define SHIT_2_BITS		2
#define SHIT_8_BITS		8


uint8_t g_Adjustment ;
uint8_t g_InitCheck ;
uint8_t g_InterruptMode ;

void (*ADC_CallBack)(uint16_t ADC_Result);

/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of ADC
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_16(void)__attribute((signal,used));

uint8_t MCAL_ADC_Init(ADC_ConfigStr_t * ADC_ConfigSt)
{
	uint8_t Local_Error = NO_ERROR;					/*Error Status : No Error*/

	/*_________________________________________________________________
	 * Configuration of ADC Module Reference Voltage
	 * ________________________________________________________________*/

	switch(ADC_ConfigSt->u8REF_Select)
	{
		case ADC_AREF_INTERNAL_VREF_OFF :			/*In Case of AREF*/

			CLR_BIT(ADMUX , ADMUX_REFS0);
			CLR_BIT(ADMUX , ADMUX_REFS1);

			break ;

		case ADC_AVCC_WITH_EXTERNAL_CAPACITOR_AT_VREF :		/*In Case of AVCC*/

			SET_BIT(ADMUX , ADMUX_REFS0);
			CLR_BIT(ADMUX , ADMUX_REFS1);

			break;

		case ADC_INTERNAL_2_56_VREF :						/*In Case of Internal 2.56v*/

			SET_BIT(ADMUX , ADMUX_REFS0);
			SET_BIT(ADMUX , ADMUX_REFS1);

			break;
		default :

			Local_Error = ERROR;				/*Error Status: Error*/

			break;
	}

	/*_________________________________________________________________
	* Configuration of ADC Value Adjustment
	* ________________________________________________________________*/

	if(Local_Error != ERROR)					/*Check if There is no Error*/
	{
		if(Local_Error == ADC_RIGHT_ADJUST || Local_Error == ADC_LEFT_ADJUST)
		{
			ASSIGN_BIT(ADMUX , ADMUX_ADLAR , ADC_ConfigSt ->u8DataAdustment);		/*Set Adjustment*/

			g_Adjustment = ADC_ConfigSt ->u8DataAdustment ;			/*Share The Configuration To the other functions*/
		}
		else
		{
			Local_Error = ERROR ; 	/*Error Status: Error*/
		}
	}

	/*_________________________________________________________________
	* Configuration of ADC Auto Trigger
	* ________________________________________________________________*/

	if(Local_Error != ERROR)
	{
		if (ADC_ConfigSt->u8AutoTriggerSource == ADC_NO_AUTO_TRIGGER)			/*Disable Auto Trigger*/
		{
			CLR_BIT(ADCSRA , ADCSRA_ADATE);
		}
		else
		{
			SET_BIT(ADCSRA , ADCSRA_ADATE);
			SFIOR = (SFIOR  &  LAST_3_BITS_CLEAR ) | ( ADC_ConfigSt->u8AutoTriggerSource  << LAST_3_BITS_SHIFT );
		}
	}

	/*_________________________________________________________________
	* Configuration of ADC Interrupt Mode
	* ________________________________________________________________*/

	if(Local_Error != ERROR)
	{
		if (ADC_ConfigSt->u8InterruptOrPolling == ADC_POLLING)			/*Disable Interrupt*/
		{
			CLR_BIT(ADCSRA , ADCSRA_ADIE);

			g_InterruptMode = ADC_POLLING;								/*Share The Configuration To the other functions*/
		}
		else if(ADC_ConfigSt->u8InterruptOrPolling == ADC_INTRRUPT)		/*Enable Interrupt*/
		{
			SET_BIT(ADCSRA , ADCSRA_ADIE);

			SET_BIT(SREG , 7);

			g_InterruptMode = ADC_INTRRUPT;								/*Share The Configuration To the other functions*/
		}

	}

	/*_________________________________________________________________
	* Configuration of ADC Prescaller
	* ________________________________________________________________*/
	if(Local_Error != ERROR)
	{
		ADCSRA = (ADCSRA & 0xF8 ) | ADC_ConfigSt->u8Prescaller ;		/*Set Prescaller*/
	}


	if(Local_Error != ERROR)
	{
		SET_BIT(ADCSRA , ADCSRA_ADEN);		/*enable ADC*/

		g_InitCheck = NO_ERROR ;			/*Initialization is complete*/
	}

	return Local_Error;
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: ADC Start Conversion
 * Input     : ADC Channel , ADC Channel Type, pointer to receive the value of conversion
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_ADC_StartCoversionBusyWait(uint8_t u8ADC_Channel , uint16_t *ptr_Result)
{
	uint8_t Local_Error = NO_ERROR;  /*Error Status : No Error*/

	if(g_InitCheck == NO_ERROR)
	{

		MCAL_DIO_u8SetPinDir(DIO_PORTA , u8ADC_Channel , DIO_INPUT);  /*set Pin To Floating Input Pin*/

		ADMUX = (ADMUX & FIRST_5_BITS_CLEAR ) | u8ADC_Channel ;			/*Enable the Channel selected*/

		SET_BIT(ADCSRA,ADCSRA_ADIF);   					/*Clear Flag*/

		SET_BIT(ADCSRA , ADCSRA_ADSC);			/*Start Conversion*/

		while(GET_BIT(ADCSRA , ADCSRA_ADIF) != TRUE);		/*Block on flag*/

		if(g_Adjustment == ADC_LEFT_ADJUST)
		{
			*ptr_Result = (uint16_t)ADCL >> SHIT_6_BITS ;
			*ptr_Result |= ((uint16_t)ADCH << SHIT_2_BITS );
		}
		else
		{
			*ptr_Result = (uint16_t) ADCL;         /*Read the low Value*/
			*ptr_Result |= (uint16_t) ADCH << SHIT_8_BITS;   /*Shift the remaining two bits and read it */
		}
	}
	else
	{
		Local_Error  = ERROR;
	}

	return Local_Error ;
}

/*_______________________________________________________________________________________________________________________________*/
/*Description: ADC Start Conversion
 * Input     : ADC Channel , ADC Channel Type, pointer to Function with parameter to use value of Conversion
 * Output    : Error Checking
 *_______________________________________________________________________________________________________________________________*/
uint8_t MCAL_ADC_StartCoversionSetCallBackISR(uint8_t u8ADC_Channel , void (*Ptr_FunctionADC)(uint16_t Copy_u16Result))
{
	uint8_t Local_Error = NO_ERROR;  /*Error Status : No Error*/

	if(g_InitCheck == NO_ERROR)
	{
		MCAL_DIO_u8SetPinDir(DIO_PORTA , u8ADC_Channel , DIO_INPUT);  /*set Pin To Floating Input Pin*/

		ADMUX = (ADMUX & FIRST_5_BITS_CLEAR ) | u8ADC_Channel ;			/*Enable the Channel selected*/

		ADC_CallBack = Ptr_FunctionADC ;

		SET_BIT(ADCSRA , ADCSRA_ADSC);			/*Start Conversion*/
	}

	return Local_Error;
}


/*_______________________________________________________________________________________________________________________________*/
/*Description: ISR of ADC
 * Input     : None
 * Output    : None
 *_______________________________________________________________________________________________________________________________*/
void __vector_16(void)
{
	uint16_t Local_ADCValue ;

	if(ADC_CallBack != NULL)
	{
		if(g_Adjustment == ADC_LEFT_ADJUST)
		{
			Local_ADCValue = (uint16_t)ADCL >> SHIT_6_BITS ;
			Local_ADCValue |= ((uint16_t)ADCH << SHIT_2_BITS );
		}
		else
		{
			Local_ADCValue = (uint16_t) ADCL;         /*Read the low Value*/
			Local_ADCValue |= (uint16_t) ADCH << SHIT_8_BITS;   /*Shift the remaining two bits and read it */
		}

		ADC_CallBack(Local_ADCValue);
	}
}
