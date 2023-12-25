/*************************************************************
 * ****************** Author : Omar Shrif *******************
 * ****************** Date   : 6-9-2022   *******************
 *************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_Interface.h"
#include "ADC_Config.h"
#include "ADC_private.h"


void ADC_voidInit(void){
	ADMUX = ADC_REF <<6;	// Voltage reference source
	ADMUX |= ADC_LA  <<5;	// Left adjustment value

	ADCSRA = ADATE <<5;		// Select the enable state of the auto trigger mode
	SET_BIT(ADCSRA, 4);		// Resets the ADC interrupt flag just in case
	ADCSRA |= ADPS<<0;		// Configure the prescaler value of the ADC clock
	SET_BIT(ADCSRA, 7);		// Enables the ADC
}


u16 ADC_u16Read(ADC_Channel_options_t Copy_u8ADCchannel){
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8ADCchannel;
	//ADMUX |= Copy_u8ADCchannel<<0;	// Selects the ADC channel
	SET_BIT(ADCSRA, 6);				// Starts the ADC conversion
	while(!GET_BIT(ADCSRA, 4));		// Wait until the conversion is completed
	SET_BIT(ADCSRA, 4);				// Clear the ADC Interrupt Flag
	return ADC_DATA;
}

f32 ADC_f32ADCtoVolt(u16 Copy_u16ADCVal){
	f32 temp_f32VoltVal = (Copy_u16ADCVal/1024.0)*ADC_V_REF;
	return temp_f32VoltVal;
}
