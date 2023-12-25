#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "Timer1_Interface.h"
#include "Servo_Interface.h"
#include "avr/delay.h"

void Servo_voidInit()
{
	DIO_voidSetPinDirection(DIO_PORTD,PIN5,OUTPUT_PIN);
	Timer1_voidInitPWM();
}
void Servo_voidMove(u16 Copy_u16Degree)
{
	Timer1_voidSetCompareMatchValueChannalA(Copy_u16Degree);
	_delay_ms(1);
}
