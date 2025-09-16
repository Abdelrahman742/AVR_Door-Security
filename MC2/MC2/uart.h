 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Abdelrahman Ibrahem
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

typedef enum
{
	BITS5=0x00,BITS6=0x02,BITS7=0x04,BITS8=0x06
}UART_BitData;

typedef enum
{
	DISABLED=0x00,EVEN_PARITY=0x20,ODD_PARITY=0x30
}UART_Parity;

typedef enum
{
	STOP_1BIT,STOP_2BIT
}UART_StopBit;

typedef enum
{
	BDR0=10,BDR1=300,BDR2=600,BDR3=1200,BDR4=2400,BDR5=4800,BDR6=9600,BDR7=14400,BDR8=19200,BDR9=38400
}UART_BaudRate;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
}UART_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const UART_ConfigType * Config_Ptr);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
