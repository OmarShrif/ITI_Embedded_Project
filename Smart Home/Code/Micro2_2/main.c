/*************************************************************
 * *********************  Team 1        **********************
 * *********************  Omar Shrif    **********************
 * *********************  Mahmoud Samy  **********************
 * *********************  Ahmed Ali     **********************
 *************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "Servo_Interface.h"
#include "Lm35_Interface.h"
#include "UART_Interface.h"
#include "avr/delay.h"

#define CLOSED		0
#define OPEN		1

#define DISABLE		2
#define ENABLE		3

#define WRONG		4
#define RIGHT		5

#define DONE		'='


void main(void)
{
	u8 Local_u8State=DISABLE;
	u8 Local_u8Trails=0;

	//Leds
	DIO_voidSetPortDirection(DIO_PORTB, OUTPUT_PORT);
	DIO_voidSetPortValue(DIO_PORTB,LOW);

	//Motor(Fan)
	DIO_voidSetPinDirection(DIO_PORTA,PIN2,OUTPUT_PIN);

	Servo_voidInit();
	ADC_voidInit();
	LCD_voidConfigDirection();
	LCD_voidInit();
	UART_voidInit();

	while(1)
	{
		Local_u8State=DISABLE;
		while(Local_u8State==DISABLE)
		{
			Servo_voidMove(ZERO);
			Local_u8State=UART_u8ReadData();
			if(Local_u8State==ENABLE)
			{
				LCD_voidGoToXY(0,0);
				LCD_voidWriteString("Welcome to Smart");
				LCD_voidGoToXY(2,1);
				LCD_voidWriteString("Home System");
				_delay_ms(5000);
				LCD_voidSendCommand(1);
				Local_u8State=CLOSED;
			}
		}
		while(Local_u8State==CLOSED && Local_u8Trails<3)
		{
			UART_voidWriteData(DONE);
			LCD_voidSendCommand(1);
			Servo_voidMove(ZERO);
			LCD_voidGoToXY(0,0);
			LCD_voidWriteString("USER:");
			u8 i=0;
			u8 j=0;
			u8 Num=0;
			while(Num!=DONE)
			{
				Num=UART_u8ReadData();
				if(Num >='0' && Num <='9' && i<4)
				{
					LCD_voidSendData(Num);
					i++;
				}
			}
			Num=UART_u8ReadData();
			if(Num == RIGHT)
			{
				LCD_voidGoToXY(0,1);
				LCD_voidWriteString("Password:");
				while(Num!=DONE)
				{
					Num=UART_u8ReadData();
					if(j<4 && Num>='0' && Num<='9')
					{
						LCD_voidGoToXY(9+j,1);
						LCD_voidSendData(Num);
						_delay_ms(100);
						LCD_voidGoToXY(9+j,1);
						LCD_voidSendData('*');
						j++;
					}
				}
				Num=UART_u8ReadData();
				if(Num == RIGHT)
				{
					LCD_voidSendCommand(1);
					LCD_voidGoToXY(5,0);
					LCD_voidWriteString("Welcome");
					_delay_ms(1000);
					LCD_voidSendCommand(1);
					Local_u8State = OPEN;
				}
				else if(Num == WRONG)
				{
					Local_u8Trails++;
					LCD_voidSendCommand(1);
					LCD_voidGoToXY(0,0);
					LCD_voidWriteString("WRONG Password");
					_delay_ms(300);
					if(Local_u8Trails<3)
					{
						LCD_voidGoToXY(4,1);
						LCD_voidWriteString("Try Again");
						_delay_ms(1000);
					}
				}
			}
			else if(Num == WRONG)
			{
				LCD_voidWriteDecimalNumber(WRONG);
				Local_u8Trails++;
				LCD_voidSendCommand(1);
				LCD_voidGoToXY(0,0);
				LCD_voidWriteString("WRONG User");
				_delay_ms(300);
				if(Local_u8Trails<3)
				{
					LCD_voidGoToXY(4,1);
					LCD_voidWriteString("Try Again");
					_delay_ms(1000);
				}
			}
		}

		if(Local_u8Trails==3)
		{
			Local_u8Trails=0;
			Local_u8State = DISABLE;
			LCD_voidSendCommand(1);
			LCD_voidGoToXY(5,0);
			LCD_voidWriteString("Goodbye");
			_delay_ms(1000);
			LCD_voidSendCommand(1);
		}
      while(Local_u8State!=DISABLE)
      {
		if(Local_u8State!=DISABLE)
		{
			Servo_voidMove(NINETY);

			//Temperature Sensor
			LCD_voidGoToXY(0,0);
			LCD_voidWriteString("Temp : ");
			LCD_voidWriteFloatNumber(Lm35_f32GetTemperature());
			LCD_voidSendData('c');
			if(Lm35_f32GetTemperature()>=26.0)
			{
				DIO_voidSetPinValue(DIO_PORTA,PIN2,HIGH);
				LCD_voidGoToXY(15,0);
				LCD_voidSendData('M');
			}
			else
			{
				DIO_voidSetPinValue(DIO_PORTA,PIN2,LOW);
				LCD_voidGoToXY(15,0);
				LCD_voidSendData(' ');
			}

			//LDR Sensor
			LCD_voidGoToXY(0,1);
			LCD_voidWriteString("On Leds : ");
			u16 Local_u16ADCVal = ADC_u16Read(ADC1);
			f32 Local_f32LDR_Volt = ADC_f32ADCtoVolt(Local_u16ADCVal);

			if(Local_f32LDR_Volt>=4.97)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b11111111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(8);
			}
			else if(Local_f32LDR_Volt>=4.95 && Local_f32LDR_Volt<4.97)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b01111111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(7);
			}
			else if(Local_f32LDR_Volt>=4.90 && Local_f32LDR_Volt<4.95)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00111111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(6);
			}
			else if(Local_f32LDR_Volt>=4.76 && Local_f32LDR_Volt<4.90)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00011111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(5);
			}
			else if(Local_f32LDR_Volt>=4.54 && Local_f32LDR_Volt<4.76)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00001111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(4);
			}
			else if(Local_f32LDR_Volt>=4.16 && Local_f32LDR_Volt<4.54)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00000111);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(3);
			}
			else if(Local_f32LDR_Volt>=3.32 && Local_f32LDR_Volt<4.16)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00000011);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(2);
			}
			else if(Local_f32LDR_Volt>=2.5 && Local_f32LDR_Volt<3.32)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00000001);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(1);
			}
			else if(Local_f32LDR_Volt<2.5)
			{
				DIO_voidSetPortValue(DIO_PORTB,0b00000000);
				LCD_voidGoToXY(11,1);
				LCD_voidWriteDecimalNumber(0);
			}
		}
      }
	}
}
