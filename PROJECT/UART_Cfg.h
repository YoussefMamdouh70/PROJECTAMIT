/*
 * UART_Cfg.h
 *
 *  Created on: Jan 8, 2021
 *      Author: kh
 */

#ifndef UART_CFG_H_
#define UART_CFG_H_

/*Options :	UART_PARITY_EVEN ,
 *          UART_PARITY_ODD  ,
 * 			UART_PARITY_DISABLE*/
#define UART_PARITY_CHECK_BIT  UART_PARITY_DISABLE

/*Options :	UART_ONE_STOP_BIT ,
 *          UART_TWO_STOP_BIT  */
#define UART_STOP_BIT  UART_ONE_STOP_BIT

/*Options :	UART_SYNC_MODE ,
 *          UART_ASYNC_MODE  */
#define UART_SYNCHRONOUS_MODE  UART_ASYNC_MODE

#endif /* UART_CFG_H_ */
