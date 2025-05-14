/*
 * GY302.cpp
 *
 * Created: 20-11-2024 17:11:35
 *  Author: ganap
 */ 

#include "GY302.h"

GY302::GY302(I2C* i2c)
{
	this->i2c = i2c;
}

float GY302::ReadLightIntensity()
{
	uint8 data[2];
		
	i2c->Start();
	i2c->SendByte(0x46);
	i2c->SendByte(0x10);
	i2c->Stop();
	_delay_ms(10);
	i2c->Start();
	i2c->SendByte(0x46);
	i2c->SendByte(0x42);
	i2c->Stop();
	i2c->Start();
	i2c->SendByte(0x46);
	i2c->SendByte(0x65);
	i2c->Stop();
	i2c->Start();
	i2c->SendByte(0x46);
	i2c->SendByte(0x10);
	i2c->Stop();
	
	_delay_ms(100);
	
	i2c->Start();
	i2c->SendByte(0x47);
	data[0] = i2c->ReadByte();
	i2c->SendACK();
	data[1] = i2c->ReadByte();
	i2c->SendNACK();
	i2c->Stop();
	
	
	unsigned int recievedData = (data[0] << 8) + data[1];
	float intensity = (recievedData/1.20f);
	return intensity;
}