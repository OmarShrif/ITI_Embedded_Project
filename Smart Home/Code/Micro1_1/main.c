/*************************************************************
 * *********************  Team 1        **********************
 * *********************  Omar Shrif    **********************
 * *********************  Mahmoud Samy  **********************
 * *********************  Ahmed Ali     **********************
 *************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "SevenSegment_Intereface.h"
#include "KeyPad_Interface.h"
#include "UART_Interface.h"
#include "avr/delay.h"

#define DISABLE		2
#define ENABLE		3

#define WRONG		4
#define RIGHT		5

#define FALSE		6
#define TRUE		7

#define DONE		'='

u8 CompareArray(u8 *Array1,u8 *Array2);

void main(void)
{
	u8 Local_u8User[4]     = {1,2,3,4};
	u8 Local_u8Password[4] = {1,2,3,4};
	u8 Local_u8Trails=3;

	//Button
	DIO_voidSetPinDirection(DIO_PORTA,PIN7,INPUT_PIN);
	DIO_voidSetPinValue(DIO_PORTA,PIN7,HIGH);

	UART_voidInit();
	KeyPad_voidInit();
	Seven_voidSegmentInit();

	while(1)
	{
		while(DIO_u8GetPinValue(DIO_PORTA,PIN7) != LOW)
		{
			_delay_ms(100);
			UART_voidWriteData(DISABLE);
			Seven_voidSegmentClear();
		}
		Seven_voidlightSegment(Local_u8Trails);
		UART_voidWriteData(ENABLE);
		while(UART_u8ReadData()!=DONE);
		u8 i=0;
		u8 j=0;
		u8 Num=0;
		while(Local_u8Trails>0)
		{
			u8 Local_u8UserBuffer[4]={0};
			u8 Local_u8PasswordBuffer[4]={0};
			//User Entry
			while(Num != DONE)
			{
				Num=KeyPad_u8GetPress();
				if(Num >='0' && Num<='9' && i<4 )
				{
					while(KeyPad_u8GetPress() >= '0' && KeyPad_u8GetPress() <= '9');
					UART_voidWriteData(Num);
					Local_u8UserBuffer[i]=Num-48;
					i++;
				}
			}
			i=0;
			while(KeyPad_u8GetPress() == DONE);
			UART_voidWriteData(DONE);
			Num=0;
			if(CompareArray(Local_u8User,Local_u8UserBuffer) == TRUE)
			{
				UART_voidWriteData(RIGHT);
				//Password Entry
				while(Num != DONE)
				{
					Num=KeyPad_u8GetPress();
					if(Num >='0' && Num<='9' && j<4 )
					{
						while(KeyPad_u8GetPress() >= '0' && KeyPad_u8GetPress() <= '9');
						UART_voidWriteData(Num);
						Local_u8PasswordBuffer[j]=Num-48;
						j++;
					}
				}
				j=0;
				while(KeyPad_u8GetPress() == DONE);
				UART_voidWriteData(DONE);
				Num=0;
				if(CompareArray(Local_u8Password,Local_u8PasswordBuffer) == TRUE)
				{
					UART_voidWriteData(RIGHT);
					Local_u8Trails=0;
				}
				else if(CompareArray(Local_u8Password,Local_u8PasswordBuffer) == FALSE)
				{
					UART_voidWriteData(WRONG);
					Local_u8Trails--;
					Seven_voidlightSegment(Local_u8Trails);
				}
			}
			else if (CompareArray(Local_u8User,Local_u8UserBuffer) == FALSE)
			{
				UART_voidWriteData(WRONG);
				Local_u8Trails--;
				Seven_voidlightSegment(Local_u8Trails);
			}
		}

		if(Local_u8Trails==0)
			Local_u8Trails=3;

	}
}

u8 CompareArray(u8 *Array1,u8 *Array2)
{
	for(u8 i =0 ; i<4 ; i++)
	{
		if(Array1[i]!=Array2[i])
			return FALSE;
	}
	return TRUE;
}
