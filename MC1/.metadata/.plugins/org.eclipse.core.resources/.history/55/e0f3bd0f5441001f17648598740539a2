/*
 * timer1.h
 *
 *  Created on: Jul 6, 2024
 *      Author: dell
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_types.h"

typedef enum
{
	Normal,CTC
}Timer1_Mode;

typedef enum
{
	No_clock,clk_1,clk_8,clk_64,clk_128,clk_256,clk_1024,falling_edge,rising_edge
}Timer1_Prescaler;

typedef struct
{
	uint16 initial_value;
	uint16 compare_value; // it will be used in compare mode only.
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

void Timer1_init(const Timer1_ConfigType * Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void(*a_ptr)(void));




#endif /* TIMER1_H_ */
