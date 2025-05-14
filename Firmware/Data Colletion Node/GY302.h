/*
 * GY302.h
 *
 * Created: 20-11-2024 17:08:48
 *  Author: ganap
 */ 


#ifndef GY302_H_
#define GY302_H_

#include "I2C.h"

class GY302
{
	private:
			I2C *i2c;
	public:
			GY302(I2C*);
			float ReadLightIntensity(); 
	
};


#endif /* GY302_H_ */