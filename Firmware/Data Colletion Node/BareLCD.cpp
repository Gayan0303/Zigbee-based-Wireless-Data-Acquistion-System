#include "BareLCD.h"

#define EN  0x04
#define RS  0x01
#define BACKLIGHT 0x08

BareLCD::BareLCD(I2C *i2c, uint8_t address) {
	this->i2c = i2c;
	this->address = address << 1;
}

void BareLCD::sendNibble(uint8_t nibble, uint8_t rs) {
	uint8_t data = (nibble & 0xF0) | BACKLIGHT;
	if (rs) data |= RS;

	i2c->Start();
	i2c->SendByte(address);
	i2c->SendByte(data | EN);
	_delay_us(1);
	i2c->SendByte(data & ~EN);
	i2c->Stop();
}

void BareLCD::sendCommand(uint8_t cmd) {
	sendNibble(cmd & 0xF0, 0);
	sendNibble((cmd << 4) & 0xF0, 0);
	_delay_ms(2);
}

void BareLCD::sendData(uint8_t data) {
	sendNibble(data & 0xF0, 1);
	sendNibble((data << 4) & 0xF0, 1);
	_delay_us(100);
}

void BareLCD::lcdInit() {
	_delay_ms(50);
	sendNibble(0x30, 0); _delay_ms(5);
	sendNibble(0x30, 0); _delay_ms(5);
	sendNibble(0x20, 0); _delay_ms(5);

	sendCommand(0x28); // 4-bit, 2-line, 5x8 font
	sendCommand(0x0C); // Display ON, Cursor OFF
	sendCommand(0x06); // Entry mode
	sendCommand(0x01); // Clear display
	_delay_ms(2);
}

void BareLCD::begin() {
	lcdInit();
}

void BareLCD::clear() {
	sendCommand(0x01);
	_delay_ms(2);
}

void BareLCD::setCursor(uint8_t col, uint8_t row) {
	uint8_t row_offsets[] = {0x00, 0x40};
	sendCommand(0x80 | (col + row_offsets[row]));
}

void BareLCD::print(const char* str) {
	clear();
	setCursor(0, 0);
	uint8_t i = 0;
	while (str[i] && i < 16) {
		sendData(str[i++]);
	}
	if (str[i]) {
		setCursor(0, 1);
		while (str[i] && i < 32) {
			sendData(str[i++]);
		}
	}
}
