/*
 * buzzer.c
 *
 *  Created on: Jul 13, 2024
 *      Author: dell
 */
#include "buzzer.h"
#include "gpio.h"
#include "std_types.h"

void Buzzer_init()
{
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID,PORT_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_HIGH);
}

void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID,LOGIC_LOW);
}

