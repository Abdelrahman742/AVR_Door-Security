/*
 * dc_motor.h
 *
 *  Created on: Jul 4, 2024
 *       Author: Abdelrahman Ibrahem Adel
 * Description: DC Motor driver
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

typedef enum
{
	CW,CCW,ST
}DcMotor_State;

void DcMotor_init();
void DcMotor_Rotate(DcMotor_State state);

#endif /* DC_MOTOR_H_ */
