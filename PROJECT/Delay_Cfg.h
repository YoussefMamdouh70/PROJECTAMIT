/*
 * Delay_Cfg.h
 *
 *  Created on: Jan 15, 2021
 *      Author: kh
 */

#ifndef DELAY_CFG_H_
#define DELAY_CFG_H_

/*
 * Prescaller * DELAY_TICK = SYSTEM_FREQUENCY * Desired_Time
 *
 * ex Desired = 1ms  , System_Frequency = 1 MHz
 *
 * Prescaller * DELAY_TICK = 1 Mhz * 1 ms = 1000
 *
 * so choose from available Prescallers for Example /8 Prescaller so  DELAY_TICK = 125
 * */
#define DELAY_PRESCALLER  F_CPU_CLOCK_64_TIMER_0

#define DELAY_TICK   125

#endif /* DELAY_CFG_H_ */
