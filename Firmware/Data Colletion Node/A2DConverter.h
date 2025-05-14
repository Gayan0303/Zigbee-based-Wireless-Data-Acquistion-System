/* 
* ADC.h
*
* Created: 30-11-2024 12:10:00
* Author: ganap
*/


#ifndef __A2DCONVERTER_H__
#define __A2DCONVERTER_H__

#include <avr/io.h>
#include "Utility.h"

typedef enum{ADC_CH0=0x00, ADC_CH1=0x01, ADC_CH2=0x02, ADC_CH3=0x03, ADC_CH4=0x04, ADC_CH5=0x05} ADC_CHANNELS;
typedef enum{DIV_2 = 0, DIV_4 = 2, DIV_8=3, DIV_16=4, DIV_32=5, DIV_64=6, DIV_128=7} ADC_PRESCALAR;
	


class A2DConverter
{
	private:
			 uint8_t _pin;
	public: 			
			static uint16 ReadValue(ADC_PRESCALAR, ADC_CHANNELS);

}; //ADC
 

#endif //__ADC_H__
