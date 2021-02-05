/*
 * I2C_program.c
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Compiler.h"

#include "AVR_I2C_REG.h"
#include "I2C_interface.h"

/*Master*/
void MCAL_I2CMASTER_InitMaster(uint8_t Copy_Prescaller )
{
	I2C_TWBR = Copy_Prescaller ;

	CLR_BIT(I2C_TWSR , 0);
	CLR_BIT(I2C_TWSR , 1);

}


void MCAL_I2CMASTER_StartCondition(void)
{
	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 5);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0));

//	while((I2C_TWSR & 0xf8) != START_ACK);

}

void MCAL_I2CMASTER_RepeatedStartcondition(void)
{
	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 5);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );

//	while((I2C_TWSR & 0xf8) != REP_START_ACK);
}

void MCAL_I2CMASTER_StopCondition(void)
{
	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 4);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );
//	while( ( GET_BIT(I2C_TWCR , 4) == 0) );
}

void MCAL_I2CMASTER_SlaveAddressRead(uint8_t Copy_u8SlaveAddress )
{
	I2C_TWDR = (Copy_u8SlaveAddress << 1 ) | 0x01;

	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 2);

	SET_BIT(I2C_TWDR , 0);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );

//	while((I2C_TWSR & 0xf8) != SLAVE_ADD_RD_ACK);

}

void MCAL_I2CMASTER_SlaveAddressWrite(uint8_t Copy_u8SlaveAddress )
{
	I2C_TWDR =( Copy_u8SlaveAddress << 1 ) | 0x00;

	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );

//	while((I2C_TWSR & 0xf8) != SLAVE_ADD_WR_ACK);
}


/*slave*/
void MCAL_I2CSLAVE_InitSlave(uint8_t Copy_u8SlaveAddress )
{
	I2C_TWAR = Copy_u8SlaveAddress << 1 ;
}


void TWI_match_write_slave(void) //Function to match the slave address and slave dirction bit(write)
{
//while((I2C_TWSR & 0xF8)!= 0xA8) // Loop till correct acknoledgement have been received
//{


I2C_TWCR=(1<<2)|(1<<7);//|(1<<6);
while( ( GET_BIT(I2C_TWCR , 7) == 0) );
//}
}

void TWI_match_read_slave(void) //Function to match the slave address and slave dirction bit(read)
{
//while((I2C_TWSR & 0xF8)!= 0x60)  // Loop till correct acknoledgement have been received
//{
// Get acknowlegement, Enable TWI, Clear TWI interrupt flag
	I2C_TWCR=(1<<2)|(1<<7); //(1<<6);
while( ( GET_BIT(I2C_TWCR , 7) == 0) );
}
//}


uint8_t I2C_Read(uint8_t * Ptr_ReadData)
{
	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );

//	while((I2C_TWSR & 0xf8) != RD_BYTE_ACK);

	return I2C_TWDR ;
}

uint8_t I2C_ReadSlave(uint8_t * Ptr_ReadData)
{
	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 2);
//	SET_BIT(I2C_TWCR , 6);

	while( ( GET_BIT(I2C_TWCR , 7) == 0) );

//	while((I2C_TWSR & 0xf8) != 0x80);

	return I2C_TWDR ;
}

void I2c_Write(uint8_t Copy_Data)
{
	I2C_TWDR = Copy_Data ;

	SET_BIT(I2C_TWCR , 7);
	SET_BIT(I2C_TWCR , 2);

	while( ( GET_BIT(I2C_TWCR , 7) == 0));

//	while((I2C_TWSR & 0xf8) != WR_BYTE_ACK);
}

void I2C_ACKEnable(void)
{
	SET_BIT(I2C_TWCR , 7);
//	SET_BIT(I2C_TWCR , 6);

	while( ( GET_BIT(I2C_TWCR , 7) == 0));
}
