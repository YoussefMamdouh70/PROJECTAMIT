/*
 * AVR_I2C_REG.h
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */

#ifndef AVR_I2C_REG_H_
#define AVR_I2C_REG_H_

#define I2C_TWCR *((volatile uint8_t *)0x56)
#define I2C_TWBR *((volatile uint8_t *)0x20)
#define I2C_TWSR *((volatile uint8_t *)0x21)
#define I2C_TWAR *((volatile uint8_t *)0x22)
#define I2C_TWDR *((volatile uint8_t *)0x23)


#endif /* AVR_I2C_REG_H_ */
