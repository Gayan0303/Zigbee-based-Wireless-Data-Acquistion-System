/* 
* I2C.cpp
*
* Created: 25-10-2024 15:40:04
* Author: VVCE
*/


#include "I2C.h"

I2C::I2C(Pin *sda, Pin *scl)
{
	this->sda = sda;
	this->scl = scl;
	this->sda->SetDirection(OUTPUT);
	this->scl->SetDirection(OUTPUT);
	this->sda->Set();
	this->scl->Set();
}

void I2C::Start()
{
	this->scl->Set();
	this->sda->Clear();	
	_delay_us(10);
	this->scl->Clear();
	_delay_us(10);
}

void I2C::Stop()
{
	this->sda->Clear();
	this->scl->Set();
	_delay_us(10);
	this->sda->Set();
	_delay_us(10);
}

void I2C::SendACK()
{
	this->sda->Clear();
	_delay_us(5);
	this->scl->Clear();
	_delay_us(5);
	this->scl->Set();
	_delay_us(5);
	this->scl->Clear();
}

void I2C::SendNACK()
{
	this->sda->Set();
	this->scl->Clear();
	_delay_us(5);
	this->scl->Set();
	_delay_us(5);
	this->scl->Clear();
}

uint8 I2C::SendByte(uint8 dataByte)
{
	uint8 pattern = 0x80, retValue;
	for(uint8 i = 0; i < 8; i++)
	{
		dataByte & pattern ? this->sda->Set() : this->sda->Clear();
		this->scl->Clear();
		_delay_us(5);
		this->scl->Set();
		_delay_us(5);
		this->scl->Clear();
		_delay_us(5);
		pattern = pattern >> 1;
	}
	this->sda->SetDirection(INPUT);
	this->scl->Clear();
	_delay_us(5);
	this->scl->Set();
	_delay_us(5);
	retValue = this->sda->Read();
	this->scl->Clear();
	_delay_us(5);
	this->sda->SetDirection(OUTPUT);
	return retValue;
}

uint8 I2C::ReadByte()
{
	uint8 dataRead = 0x00;
	this->sda->SetDirection(INPUT);
	for(uint8 i = 0; i < 7; i++)
	{
		this->scl->Clear();
		_delay_us(5);
		this->scl->Set();
		_delay_us(5);
		dataRead |= this->sda->Read();
		this->scl->Clear();
		_delay_us(5);
		dataRead = dataRead << 1;
	}
	this->scl->Clear();
	_delay_us(5);
	this->scl->Set();
	_delay_us(5);
	dataRead |= this->sda->Read();
	this->scl->Clear();
	_delay_us(5);
	this->sda->SetDirection(OUTPUT);
	return dataRead;
}