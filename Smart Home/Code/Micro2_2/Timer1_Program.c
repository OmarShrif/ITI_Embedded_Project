/*************************************************************
 * ****************** Author : Omar Shrif *******************
 * ****************** Date   : 8-9-2022   *******************
 *************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "Timer1_Interface.h"
#include "Timer1_Register.h"


void Timer1_voidInitPWM()
{
	//Select Compare Output Mode Fast PWM Mode Non Inverted
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);
	SET_BIT(TCCR1A,TCCR1A_COM1A1);

	//Select Mode 14
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	//Select PreScaler 8
	CLR_BIT(TCCR1B,TCCR1B_CS10);
	SET_BIT(TCCR1B,TCCR1B_CS11);
	CLR_BIT(TCCR1B,TCCR1B_CS12);

	//Set OverFlow Value for 20 msec
	ICR1 = 20000;

	//Set Compare Value for 0.75 msec
	OCR1A = 750;
}

void Timer1_voidSetCompareMatchValueChannalA(u16 Copy_u16CompareValue)
{
	OCR1A = Copy_u16CompareValue;
}
