/* 
* Pin.h
*
* Created: 25-10-2024 12:39:50
* Author: VVCE
*/


#ifndef __PIN_H__
#define __PIN_H__

#include <avr/io.h>
#include "Utility.h"

enum IOPORT {IOPORTB, IOPORTC, IOPORTD};
enum IODIRECTION {INPUT, OUTPUT};

class Pin
{
	private:
			IOPORT port;
			IODIRECTION direction;
			uint8 position;
	public:
			Pin(const Pin&);
			Pin(IOPORT, uint8, IODIRECTION);
			void SetDirection(IODIRECTION);
			void Set();
			void Clear();
			void Toggle();
			uint8 Read();
};

#endif //__PIN_H__
