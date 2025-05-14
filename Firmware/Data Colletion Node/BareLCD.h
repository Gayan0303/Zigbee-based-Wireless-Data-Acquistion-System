#ifndef __BARELCD_H__
#define __BARELCD_H__

#include "I2C.h"
#include <avr/io.h>
#include <util/delay.h>

class BareLCD {
	private:
	I2C *i2c;
	uint8_t address;

	void sendNibble(uint8_t nibble, uint8_t rs);
	void sendCommand(uint8_t cmd);
	void sendData(uint8_t data);
	void lcdInit();

	public:
	BareLCD(I2C *i2c, uint8_t address = 0x27);
	void begin();
	void clear();
	void setCursor(uint8_t col, uint8_t row);
	void print(const char* str);
};

#endif
