/****************************************************************
 * ****************** Author : Omar Shrif ***********************
 * ****************** Data   : 31-8-2022  ***********************
 ****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "LCD_Config.h"
#include "LCD_Interface.h"

#include <util/delay.h>

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS by Low for Command*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_RS_PIN , LOW);

	/*Set RW by Low for Write*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_RW_PIN , LOW);

	/*Send the Command*/
	DIO_voidSetPortValue(LCD_DATA_PORT , Copy_u8Command);

	/*Enable LCD*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_E_PIN , HIGH);
	_delay_ms(2); // wait till it become high
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_E_PIN , LOW);
}

void LCD_voidSendData(u8 Copy_u8Data)
{
	/*Set RS by High for Data*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_RS_PIN , HIGH);

	/*Set RW by Low for Write*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_RW_PIN , LOW);

	/*Send the Data*/
	DIO_voidSetPortValue(LCD_DATA_PORT , Copy_u8Data);

	/*Enable LCD*/
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_E_PIN , HIGH);
	_delay_ms(2); // wait till it become high
	DIO_voidSetPinValue(LCD_CRTL_PORT , LCD_E_PIN , LOW);

}

void LCD_voidInit()
{
	/*Wait after the power on for 35 ms*/
	_delay_ms(35);

	/*Function Set
	 * 2 Lines  - 5x8 size */
	LCD_voidSendCommand(0b00111100);

	/*Display on/off Control
	 * Display on  -  Cursor off  -  Blink off */
	LCD_voidSendCommand(0b00001100);

	/*Display Clear */
	LCD_voidSendCommand(0b00000001);

}

void LCD_voidWriteString(u8* Copy_u8String)
{
	u8 Local_u8Counter = 0;

	while(Copy_u8String[Local_u8Counter] != '\0')
	{
		LCD_voidSendData(Copy_u8String[Local_u8Counter]);
		Local_u8Counter++;
	}
}

void LCD_voidWriteDecimalNumber(s16 Copy_s16Number)
{
	if(Copy_s16Number>=0 && Copy_s16Number<=9)
	LCD_voidSendData(Copy_s16Number+48);
	else if(Copy_s16Number>(-10000) && Copy_s16Number<=(-1))
	{
		LCD_voidSendData('-');
		LCD_voidWriteDecimalNumber((-1)*Copy_s16Number);
	}
	else if(Copy_s16Number>9 && Copy_s16Number<100)
	{
		LCD_voidWriteDecimalNumber(Copy_s16Number/10);
		LCD_voidWriteDecimalNumber(Copy_s16Number%10);
	}
	else if(Copy_s16Number>=100 && Copy_s16Number<1000)
	{
		LCD_voidWriteDecimalNumber(Copy_s16Number/10);
		LCD_voidWriteDecimalNumber(Copy_s16Number%10);
	}
	else if(Copy_s16Number>=1000 && Copy_s16Number<10000)
	{
		LCD_voidWriteDecimalNumber(Copy_s16Number/10);
		LCD_voidWriteDecimalNumber(Copy_s16Number%10);
	}
}

void LCD_voidWriteFloatNumber(f32 Copy_f32Number)
{
	LCD_voidWriteDecimalNumber((s16)Copy_f32Number);
	LCD_voidSendData('.');
	if(((s16)(Copy_f32Number*10))%((s16)(Copy_f32Number)) > 0)
		LCD_voidWriteDecimalNumber(((s16)(Copy_f32Number*10))%((s16)(Copy_f32Number)));
	else
		LCD_voidWriteDecimalNumber(((s16)(Copy_f32Number*(-10)))%((s16)((-1)*Copy_f32Number)));

}

void LCD_voidWriteStringNumber(u16 Copy_u16Number)
{
	u32 num[8];
	itoa(Copy_u16Number,num,10);
	LCD_voidWriteString(num);
}

void LCD_voidConfigDirection()
{
	/*Set the direction for LCD pins */
	DIO_voidSetPortDirection(LCD_DATA_PORT, OUTPUT_PORT);
	DIO_voidSetPinDirection(LCD_CRTL_PORT , LCD_RS_PIN , OUTPUT_PIN);
	DIO_voidSetPinDirection(LCD_CRTL_PORT , LCD_RW_PIN , OUTPUT_PIN);
	DIO_voidSetPinDirection(LCD_CRTL_PORT , LCD_E_PIN  , OUTPUT_PIN);
}


void LCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8DDRAM_Address;
	if(Copy_u8YPos == LCD_LINE_ONE)
	{
		Local_u8DDRAM_Address = Copy_u8XPos;
	}
	else if(Copy_u8YPos == LCD_LINE_TWO)
	{
		Local_u8DDRAM_Address = Copy_u8XPos+0x40;
	}

	LCD_voidSendCommand(Local_u8DDRAM_Address+128);
}


void LCD_voidWriteSpecialCharacter(u8 *Copy_u8XPattern,u8 Copy_u8XPatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAM_Address = Copy_u8XPatternNumber*8; //Address at CGRAM with number =Copy_u8XPatternNumber

	LCD_voidSendCommand(Local_u8CGRAM_Address+64);

	for(u8 Local_u8Counter=0 ; Local_u8Counter<8 ; Local_u8Counter++)
	{
		LCD_voidSendData(Copy_u8XPattern[Local_u8Counter]);
	}

	LCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos); //DDRAM Location selection

	LCD_voidSendData(Copy_u8XPatternNumber); //DDRAM prints the value saved at address Copy_u8XPatternNumber
}

