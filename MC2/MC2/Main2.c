/*
 * Main2.c
 *
 *  Created on: Jul 13, 2024
 *      Author: Abdelrahman Ibrahem Adel
*/
/*****************************header files*********************************/
#include<avr/io.h>
#include<util/delay.h>
#include "external_eeprom.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "timer1.h"
#include "twi.h"
#include "uart.h"

/**************************************************************************/
/*****************************Definitions**********************************/
#define EEPROM_PASSWORD_ADDRESS		0x0311
#define PASSWORD_LENGTH             5
#define GET_READY 			        0x10
/*****************************Global Variables*****************************/
/**************************************************************************/
uint8 Step1 = 1;
uint8 Step2 = 0;
uint8 counter=1;
uint8 WRONG_PASS = 0;
uint8 f_OPEN_DOOR =0; /* Flag When User Want To Open Door */
uint8 f_CHANGE_PASSWORD =0; /* Flag When User Want To Change Password */
/**************************************************************************/
/*****************************Global Arrays********************************/
uint8 pass1[5];
uint8 pass2[5];
uint8 in_pass[5];
uint8 EEPROM_PASS[5];
uint8 CHECK_PASS[5];
uint8 charactar_check='#';
/****************************Functions*************************************/
/**************************************************************************/
void Recive_pass(uint8 *pass)
{
	uint8 i;
	for(i=0; i < PASSWORD_LENGTH ;i++)
	{
		pass[i]=UART_recieveByte();
	}
}
void EEPROM_writePassword(uint8 *password)
{
	uint8 i;
    for (i = 0; i < PASSWORD_LENGTH; i++)
    {
    	EEPROM_writeByte((EEPROM_PASSWORD_ADDRESS + i) , password[i]);
    	_delay_ms(10);
    }
}
void EEPROM_readPassword(uint8 *password)
{
	uint8 i;
    for (i = 0; i < PASSWORD_LENGTH; i++)
    {
    	EEPROM_readByte(EEPROM_PASSWORD_ADDRESS + i,&password[i]);
    	_delay_ms(10);
    }
}
uint8 EEPROM_verifyPassword(uint8 *input_Password)
{
    uint8 stored_Password[PASSWORD_LENGTH];
    EEPROM_readPassword(stored_Password);
    uint8 i;
    for (i = 0; i < PASSWORD_LENGTH ; i++)
    {
        if (input_Password[i] != stored_Password[i])
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
	/**************************Initialization***************************/
	Timer1_ConfigType Timer1_Configurations={0,0,clk_1,Normal};
	TWI_ConfigType TWI_Configurations = {MASTER_ADDRESS,RATE1};
	UART_ConfigType UART_Configurations = {BITS8,EVEN_PARITY,STOP_1BIT,BDR6};
	SREG |=(1<<7);
	Buzzer_init();
	DcMotor_init();
	Timer1_init(&Timer1_Configurations);
	TWI_init(&TWI_Configurations);
	UART_init(&UART_Configurations);
	/*******************************************************************/

	while(1)
	{
		if(Step1==1)
		{
			uint8 i;

			while(UART_recieveByte() != GET_READY){}

			Recive_pass(pass1);
			Recive_pass(pass2);

			for(i=0; i<PASSWORD_LENGTH ;i++)
			{
				if(pass1[i] != pass2[i])
				{
					charactar_check='N';
				}
			}

			if(charactar_check == '#')
			{
				EEPROM_writePassword(pass1);
				UART_sendByte(charactar_check);
				Step2=1;
				Step1=0;
			}
			else
			{
				UART_sendByte(charactar_check);
			}
		}
		if(Step2 ==1)
		{
			Step2=0;

			/* Don't Exit While(1) Until You Receive From UART Of HMI_ECU */
			while(1)
			{
				if(UART_recieveByte() == '-') /* If The User Pressed '-' Button in Keypad Of HMI_ECU */
				{
					/* Go To Change Password Settings */
					f_CHANGE_PASSWORD=1;
					break;

				}
				else /* If The User Pressed '+' Button in Keypad Of HMI_ECU */
				{
					/* Go To Open Door Settings */
					f_OPEN_DOOR=1;
					break;
				}
			}
		}

		/* Open Door Settings */
		if(f_OPEN_DOOR == 1)
		{
			UART_sendByte('A');
			Recive_pass(in_pass); /* Receive USER Password From HMI_ECU */
			if(EEPROM_verifyPassword(in_pass)) /* If The Two Passwords Are Identical */
			{
				/* Open Door By Rotating Motor Then Got To Main Option Settings */
				DcMotor_Rotate(CW);
				_delay_ms(15000);
				DcMotor_Rotate(ST);
				_delay_ms(3000);
				DcMotor_Rotate(CCW);
				_delay_ms(15000);
				DcMotor_Rotate(ST);
				Step2 = 1;
				Step1 = 0;
				f_OPEN_DOOR = 0;
				f_CHANGE_PASSWORD=0;
			}
			else
			{
				/* Will Go To Wrong Password Settings */
				UART_sendByte('B');
				f_CHANGE_PASSWORD=0;
				f_OPEN_DOOR = 0;
				WRONG_PASS = 1;
				Step2=0;
				Step1=0;
			}
		}

		/* Change Password Settings */
		if(f_CHANGE_PASSWORD == 1)
		{
			Recive_pass(in_pass); /* Receive USER Password From HMI_ECU */

			if(EEPROM_verifyPassword(in_pass)) /* If The Two Passwords Are Identical */
			{
				/* Go To System Password Settings */
				UART_sendByte('A');
				Step1 = 1;
				Step2 = 0;
				f_CHANGE_PASSWORD=0;
				f_OPEN_DOOR = 0;
			}
			else
			{
				/* Will Go To Wrong Password Settings */
				UART_sendByte('B');
				f_OPEN_DOOR = 0;
				f_CHANGE_PASSWORD=0;
				WRONG_PASS = 1;
				Step2=0;
				Step1=0;
			}
		}

		/* Wrong Password Settings */
		if(WRONG_PASS==1)
		{
			/* Sending This Byte To Synchronize The Two System With Each Other */
			while(UART_recieveByte() != GET_READY){}

		/* Don't Exit While(1) Until You Receive From UART Of HMI_ECU */
		while(1)
		{
			Recive_pass(CHECK_PASS);  /* Receive Check Password From HMI_ECU */
			if(EEPROM_verifyPassword(in_pass)) /* If The Two Passwords Are Identical */
			{
				/* Go To Main Option Settings */
				UART_sendByte('X');
				counter=0;
				Step2=1;
				WRONG_PASS=0;
				Step1=0;
				break;
			}
			else
			{
				/* You Will Still In Wrong Password Settings And Counter Of Wrong Passwords Will Increment */
				UART_sendByte('Y');
				counter++;
				WRONG_PASS = 1;
				Step2=0;
				Step1=0;
				break;
			}
		}
			if(counter==3) /*If The User Enters Wrong Password Three Times */
			{
				/* Buzzer Will Be ON Then Go To Main Option Settings Again */
				counter=0;
				Buzzer_on();
				_delay_ms(60000);
				Step2 = 1;
				Step1=0;
				WRONG_PASS=0;

			}
		}
	}
}
