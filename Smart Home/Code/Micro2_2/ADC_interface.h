/*************************************************************
 * ****************** Author : Omar Shrif *******************
 * ****************** Date   : 6-9-2022   *******************
 *************************************************************/

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

typedef enum{
	AREF,
	AVCC,
	RES,
	INTERNAL_2_56
}ADC_ref_options_t;

typedef enum{
	Right_adj,
	Left_adj
}ADC_left_adjustment_options_t;


typedef enum{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7
}ADC_Channel_options_t;

typedef enum{
	Disable,
	Enable
}ADC_Enable_options_t;

typedef enum{
	DIV_2 = 1,
	DIV_4,
	DIV_8,
	DIV_16,
	DIV_32,
	DIV_64,
	DIV_128
}ADC_Prescaler_options_t;

void ADC_voidInit(void);


u16 ADC_u16Read(ADC_Channel_options_t Copy_u8ADCchannel);

f32 ADC_f32ADCtoVolt(u16 Copy_u16ADCVal);

#endif /* ADC_INTERFACE_H_ */
