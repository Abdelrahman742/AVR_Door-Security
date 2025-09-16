/*
 * dc_motor.c
 *
 *  Created on: Jul 4, 2024
 *      Author: Abdelrahman Ibrahem Adel
 * Description: DC Motor driver
 */
#include "dc_motor.h"
#include "gpio.h"
#include "pwm.h"
#include <avr/io.h>

void DcMotor_init()
{
	GPIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);
	GPIO_setupPinDirection(PORTA_ID,PIN1_ID,PIN_OUTPUT);
	GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
}
void DcMotor_Rotate(DcMotor_State state)
{
	PWM_Timer0_Init(255);
	if(state==CW)
	{
		GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_HIGH);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
	}
	else if(state==CCW)
	{
		GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_HIGH);
	}
	else
	{
		GPIO_writePin(PORTA_ID,PIN0_ID,LOGIC_LOW);
		GPIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
	}
}
