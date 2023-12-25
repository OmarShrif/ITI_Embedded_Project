/****************************************************************
 * ****************** Author : Omar Shrif ***********************
 * ****************** Data   : 31-8-2022  ***********************
 ****************************************************************/
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidInit();

void LCD_voidConfigDirection();

void LCD_voidWriteString(u8 * Copy_u8String);

void LCD_voidWriteDecimalNumber(s16 Copy_s16Number);

void LCD_voidWriteFloatNumber(f32 Copy_f32Number);

void LCD_voidWriteStringNumber(u16 Copy_u16Number);

void LCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

void LCD_voidWriteSpecialCharacter(u8 *Copy_u8XPattern,u8 Copy_u8XPatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos);


#endif /* LCD_INTERFACE_H_ */
