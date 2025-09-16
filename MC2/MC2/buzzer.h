/*
 * buzzer.h
 *
 *  Created on: Jul 13, 2024
 *      Author: dell
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#define BUZZER_PORT_ID                PORTD_ID
#define BUZZER_PIN_ID                 PIN7_ID

void Buzzer_init();
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
