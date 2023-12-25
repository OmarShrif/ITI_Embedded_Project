/*************************************************************
 * ****************** Author : Adel Khaled *******************
 * ****************** Date   : 9-11-2022   *******************
 *************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_Register.h"
#include "UART_Interface.h"

void UART_voidInit()
{
	/*Select the character size in bit 2*/
	CLR_BIT(UCSRB , UCSRB_UCSZ2);

	/*Select UCSRC register
	 * - Asynchronous mode
	 * - no parity
	 * - 1 stop bit
	 * - 8 bit character size
	 * - polarity = 0*/
	UCSRC = 0b10000110;

	/*Set the baudrate 9600 bps*/
	UBRRL = 51;

	/*Enable the RX and TX*/
	SET_BIT(UCSRB , UCSRB_RXEN);
	SET_BIT(UCSRB , UCSRB_TXEN);
}

void UART_voidWriteData(u8 Copy_u8Data)
{
	/*Waiting until the transmit buffer empty and ready for new data*/
	while(GET_BIT(UCSRA , UCSRA_UDRE) == 0);

	/*Put the new data*/
	UDR = Copy_u8Data;
}

u8 UART_u8ReadData()
{
	/*Waiting until the receive buffer complete and the data be ready in UDR*/
	while(GET_BIT(UCSRA , UCSRA_RXC) == 0);

	/*Read or return the data */
	return UDR;
}



