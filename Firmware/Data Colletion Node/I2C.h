/* 
* I2C.h
*
* Created: 25-10-2024 15:40:04
* Author: VVCE
*/


#ifndef __I2C_H__
#define __I2C_H__

#include <util/delay.h>
#include "Pin.h"

class I2C
{
	private:
			 Pin *sda;
			 Pin *scl;
	public:
			I2C(Pin*, Pin*);
			void Start();
			void Stop();
			void SendACK();
			void SendNACK();
			uint8 SendByte(uint8);
			uint8 ReadByte();
}; 

#endif //__I2C_H__
