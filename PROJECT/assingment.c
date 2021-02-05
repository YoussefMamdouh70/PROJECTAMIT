#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "SPI_interface.h"
#include "INT_interface.h"
#include "S_SEGMENT.h"
#include "TIMER_interface.h"
#include "AVR_TIMER_REG.h"
#include "AVR_INT_REG.h"
#include "avr/interrupt.h"
#include "UART_interface.h"
#include "Compiler.h"

#include  "AVR_INT_REG.h"
#include <avr/delay.h>


//#define FOCS 1000000
//#define BAUD 9600
//#define SS FOCS/16/BAUD-1

//
//void USART_INT(uint32_t ss)
//{
//	UBRRH = (uint8_t)(ss>>1);
//	UBRRL = (uint8_t)ss;
//
//	SET_BIT(UCSRB,RXEN);
//	SET_BIT(UCSRB,TXEN);
//
//	SET_BIT(UCSRC,URSEL);
//	SET_BIT(UCSRC,USBS);
//	SET_BIT(UCSRC,UCSZ0);
//	SET_BIT(UCSRC,UCSZ1);
//
//
//}

//void UART_TRANS(uint8_t data)
//{
//	while(GET_BIT(UCSRA,UDRE)!=1)
//	{
//		UDR=data;
//	}
//}

//
//uint8_t UART_REC(void)
//{
//	while(GET_BIT(UCSRA,RXC)==0)
//	{
//
//	}
//
//	return UDR;
//}




int main()
{

  uint16_t  ptr;
  uint8_t  recive;
  str_UartConfg_t conf ={9600,3,0};
  MCAL_UART_init(&conf);
  MCAL_SPI_MasterInit(SPI_MASTER_DOUBLE_FREQUENCY_64);



while(1)
{
	MCAL_UART_recieveByteBusyWait(&ptr);
	if(ptr=='1')
	{
		MCAL_SPI_Master_DataBusyWait(ptr,&recive);
	}
	else if(ptr=='0')
	{
		MCAL_SPI_Master_DataBusyWait(ptr,&recive);
	}

}
}










