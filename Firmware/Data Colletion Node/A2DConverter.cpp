/* 
* ADC.cpp
*
* Created: 30-11-2024 12:10:00
* Author: ganap
*/


#include "A2DConverter.h"


uint16 A2DConverter::ReadValue(ADC_PRESCALAR prescalar, ADC_CHANNELS channel)
{
	uint16 valueRead;
	
	ADMUX = 0x00;
	ADCSRA = 0x00;
	
	ADMUX |= (1 << REFS0)|channel;
	ADCSRA |= (1 << ADEN)|(1 << ADSC)|prescalar;
	while(!(ADCSRA & (1 << ADIF)));	
	valueRead = (ADCL | (ADCH<<8));
	ADCSRA = 0x00;
	return valueRead;
}


