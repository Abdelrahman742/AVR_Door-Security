/*
 * timer1.c
 *
 *  Created on: Jul 6, 2024
 *      Author: dell
 */
#include "timer1.h"
#include<avr/io.h>
#include <avr/interrupt.h>

static volatile void (*Timer1_callback)(void) = NULL_PTR;

ISR(TIMER1_COMPA_vect)
{
	if(Timer1_callback != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*Timer1_callback)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_OVF_vect)
{
	if(Timer1_callback != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*Timer1_callback)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

void Timer1_init(const Timer1_ConfigType * Config_Ptr)
{
	TCNT1 = Config_Ptr->initial_value;
	OCR1A = Config_Ptr->compare_value;
	TCCR1A |= (1<<FOC1A) | (1<<FOC1B);
	TCCR1B = (TCCR1B & 0xF7) | ((Config_Ptr->mode)<<3);
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->prescaler);
	if (Config_Ptr->mode == CTC)
	{
		TIMSK |= (1 << OCIE1A);  // Enable Compare Match A interrupt
	}
	else
	{
		TIMSK |= (1 << TOIE1);  // Enable Overflow interrupt
	}
}

void Timer1_deInit(void)
{
	TCNT1=0;
	OCR1A=0;
	TCCR1A=0;
	TCCR1B=0;
	TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));  // Disable interrupts
	Timer1_callback = NULL_PTR;
}

void Timer1_setCallBack(void(*b_ptr)(void))
{
	Timer1_callback = b_ptr;
}
