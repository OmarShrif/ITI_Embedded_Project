
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"
#include "SevenSegment_Config.h"
#include "SevenSegment_Intereface.h"

void Seven_voidSegmentInit()
{
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN0,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN1,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN2,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN3,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN4,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN5,OUTPUT_PIN);
	DIO_voidSetPinDirection(SEGMENT_PORT,SEGMENT_PIN6,OUTPUT_PIN);
}

void Seven_voidSegmentClear()
{
	u8 NotUsed = DIO_u8GetPinValue(SEGMENT_PORT,SEGMENT_NOT_USED_PIN);
	DIO_voidSetPortValue(SEGMENT_PORT,LOW)  ;
	DIO_voidSetPinValue(SEGMENT_PORT,SEGMENT_NOT_USED_PIN,NotUsed);
}

void Seven_voidlightSegment(u8 Number)
{
	u8 NotUsed = DIO_u8GetPinValue(SEGMENT_PORT,SEGMENT_NOT_USED_PIN);
	switch (Number)
	{
		case (0) : DIO_voidSetPortValue(SEGMENT_PORT,63)  ; break ;
		case (1) : DIO_voidSetPortValue(SEGMENT_PORT,6)   ; break ;
		case (2) : DIO_voidSetPortValue(SEGMENT_PORT,91)  ; break ;
		case (3) : DIO_voidSetPortValue(SEGMENT_PORT,79)  ; break ;
		case (4) : DIO_voidSetPortValue(SEGMENT_PORT,102) ; break ;
		case (5) : DIO_voidSetPortValue(SEGMENT_PORT,109) ; break ;
		case (6) : DIO_voidSetPortValue(SEGMENT_PORT,125) ; break ;
		case (7) : DIO_voidSetPortValue(SEGMENT_PORT,7)   ; break ;
		case (8) : DIO_voidSetPortValue(SEGMENT_PORT,127) ; break ;
		case (9) : DIO_voidSetPortValue(SEGMENT_PORT,111) ; break ;
		default  : break ;
	}
	DIO_voidSetPinValue(SEGMENT_PORT,SEGMENT_NOT_USED_PIN,NotUsed);
}
