/*
 * I2C_interface.h
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */

#ifndef I2C_INTERFACE_H_
#define I2C_INTERFACE_H_

#define START_ACK 0x08
#define REP_START_ACK 0x10
#define SLAVE_ADD_WR_ACK 0x18
#define SLAVE_ADD_RD_ACK 0x40
#define WR_BYTE_ACK 0x28
#define WR_BYTE_NACK 0x30
#define RD_BYTE_ACK 0x58
#define RD_BYTE_NACK 0x50
//#define START_ACK 0xA8
//#define START_ACK 0x60
//#define START_ACK 0x80
//#define START_ACK 0xC0
/*Master*/
void MCAL_I2CMASTER_InitMaster(uint8_t Copy_Prescaller );


void MCAL_I2CMASTER_StartCondition(void);

void MCAL_I2CMASTER_RepeatedStartcondition(void);

void MCAL_I2CMASTER_StopCondition(void);

void MCAL_I2CMASTER_SlaveAddressRead(uint8_t Copy_u8SlaveAddress );

void MCAL_I2CMASTER_SlaveAddressWrite(uint8_t Copy_u8SlaveAddress );


/*slave*/
void MCAL_I2CSLAVE_InitSlave(uint8_t Copy_u8SlaveAddress );

void TWI_match_read_slave(void) ;//Function to match the slave address and slave dirction bit(read)
void TWI_match_write_slave(void);
uint8_t I2C_ReadSlave(uint8_t * Ptr_ReadData);


uint8_t I2C_Read(uint8_t * Ptr_ReadData);

void I2C_ACKEnable(void);

void I2c_Write(uint8_t Copy_Data);
#endif /* I2C_INTERFACE_H_ */
