/*
 * pwm.c
 *
 *  Created on: Jul 5, 2024
 *       Author: Abdelrahman Ibrahem Adel
 * Description: PWM driver
 */
#include<avr/io.h>
#include "pwm.h"
#include "gpio.h"

void PWM_Timer0_Init(uint8 set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value

	OCR0  = set_duty_cycle; // Set Compare Value

	GPIO_setupPinDirection(PORTA_ID,PIN2_ID,PIN_OUTPUT); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);
}

