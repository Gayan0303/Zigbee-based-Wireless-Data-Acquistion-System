/* 
* AHT10.cpp
*
* Created: 21-11-2024 17:15:38
* Author: ganap
*/


#include "AHT10.h"

AHT10::AHT10(I2C* i2c)
{
	this->i2c = i2c;
}


void AHT10::ReadTemperatureAndHumidity(float* temperature, float* humidity)
{
	uint8 Data[6];
	
	i2c->Start();
	i2c->SendByte(0x70);
	i2c->SendByte(0xAC);
	i2c->SendByte(0x33);
	i2c->SendByte(0x00);
	i2c->Stop();

	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x99);
	i2c->SendNACK();
	i2c->Stop();
	
	_delay_ms(10);
	
	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x99);
	i2c->SendNACK();
	i2c->Stop();
	
	_delay_ms(10);
	
	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x99);
	i2c->SendNACK();
	i2c->Stop();
	
	_delay_ms(10);
	
	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x99);
	i2c->SendNACK();
	i2c->Stop();
	
	_delay_ms(10);
	
	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x99);
	i2c->SendNACK();
	i2c->Stop();
	
	_delay_ms(10);
	
	i2c->Start();
	i2c->SendByte(0x71);
	i2c->SendByte(0x19);
	i2c->Stop();
	
	i2c->Start();
	i2c->SendByte(0x71);
	Data[0] = i2c->ReadByte();
	i2c->SendACK();
	Data[1] = i2c->ReadByte();
	i2c->SendACK();
	Data[2] = i2c->ReadByte();
	i2c->SendACK();
	Data[3] = i2c->ReadByte();
	i2c->SendACK();
	Data[4] = i2c->ReadByte();
	i2c->SendACK();
	Data[5] = i2c->ReadByte();
	i2c->SendNACK();
	i2c->Stop();
	
	uint32 rawTemperatureData = ((Data[3] & 0x0F) * 65536) + (Data[4] * 256) + Data[5];
	*temperature = (rawTemperatureData * 0.000191f) - 50.0f;
	
	uint32 rawHumidityData = rawHumidityData = ((Data[3] & 0xF0) >> 4) + (Data[2] << 4) + ((uint32)Data[1]<< 12);;
	*humidity = rawHumidityData * 0.000095f;
	
	
	
}