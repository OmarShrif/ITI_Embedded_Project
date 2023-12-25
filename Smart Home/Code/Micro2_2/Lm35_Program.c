

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_Interface.h"

#include "LCD_Interface.h"
#include "ADC_Interface.h"
#include "Lm35_Config.h"
#include "Lm35_Interface.h"
#include "avr/delay.h"

f32 Lm35_f32GetTemperature()
{
	u16 ADC_val = ADC_u16Read(LM35_PIN);
	f32 volt = ADC_f32ADCtoVolt(ADC_val);
	f32 mvolt = volt*1000;
	f32 temp = mvolt/10;
	return temp;
}
