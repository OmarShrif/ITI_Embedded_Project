/****************************************************************
 * ****************** Author : Omar Shrif ***********************
 * ****************** Data   : 1-9-2022   ***********************
 ****************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "KeyPad_config.h"
#include "KeyPad_Interface.h"

#include <util/delay.h>

u8 Rows[4] = {KEYPAD_ROW1_PIN, KEYPAD_ROW2_PIN, KEYPAD_ROW3_PIN, KEYPAD_ROW4_PIN};
u8 Cols[4] = {KEYPAD_COL1_PIN, KEYPAD_COL2_PIN, KEYPAD_COL3_PIN, KEYPAD_COL4_PIN};

void KeyPad_voidInit(void){

	for(u8 rowCounter = 0; rowCounter<4;rowCounter++){
		DIO_voidSetPinDirection(KEYPAD_PORT,Rows[rowCounter],OUTPUT_PIN);
		DIO_voidSetPinValue(KEYPAD_PORT,Rows[rowCounter],HIGH);
	}

	for(u8 colCounter = 0; colCounter<4;colCounter++){
		DIO_voidSetPinDirection(KEYPAD_PORT,Cols[colCounter],INPUT_PIN);
		DIO_voidSetPinValue(KEYPAD_PORT,Cols[colCounter],HIGH);
	}
}

u8 KeyPad_u8GetPress(void){
	u8 Local_u8Col;
	u8 x = KEYPAD_NOT_PRESSED;
	for(u8 rowCounter=0; rowCounter<4;rowCounter++){
		KeyPad_voidSelectLine(Rows[rowCounter]);
		Local_u8Col = KeyPad_u8ReadButton(Rows[rowCounter]);
		if(Local_u8Col != KEYPAD_NOT_PRESSED)
			x = (rowCounter*4)+Local_u8Col;
		_delay_ms(2);
	}
	return Keypad_Char[x];
}

u8 KeyPad_u8ReadButton(u8 Copy_u8Line){

	for(u8 colCounter=0; colCounter<4;colCounter++){
		if(DIO_u8GetPinValue(KEYPAD_PORT, Cols[colCounter]) == LOW){
			DIO_voidSetPinValue(KEYPAD_PORT, Copy_u8Line, HIGH);
			return colCounter;
		}
	}

	DIO_voidSetPinValue(KEYPAD_PORT, Copy_u8Line, HIGH);
	return KEYPAD_NOT_PRESSED;


}
void KeyPad_voidSelectLine(u8 Copy_u8Line){
	DIO_voidSetPinValue(KEYPAD_PORT, Copy_u8Line, LOW);
}
