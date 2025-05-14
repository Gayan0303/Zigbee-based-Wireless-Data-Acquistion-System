/* 
* AHT10.h
*
* Created: 21-11-2024 17:15:38
* Author: ganap
*/


#ifndef __AHT10_H__
#define __AHT10_H__

#include "I2C.h"

class AHT10
{
	
	private:
			I2C *i2c;
	public:
			AHT10(I2C*);			
			void ReadTemperatureAndHumidity(float*, float*);

}; //AHT10

#endif //__AHT10_H__
