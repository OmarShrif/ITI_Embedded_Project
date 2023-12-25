/*************************************************************
 * ****************** Author : Adel Khaled *******************
 * ****************** Date   : 9-11-2022   *******************
 *************************************************************/
#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#define UDR                     *((volatile u8*)0x2C)

#define UCSRA                   *((volatile u8*)0x2B)
#define UCSRA_RXC               7
#define UCSRA_UDRE              5

#define UCSRB                   *((volatile u8*)0x2A)
#define UCSRB_RXEN              4
#define UCSRB_TXEN              3
#define UCSRB_UCSZ2             2

#define UCSRC                   *((volatile u8*)0x40)
#define UBRRL                   *((volatile u8*)0x29)

#endif /* UART_REGISTER_H_ */
