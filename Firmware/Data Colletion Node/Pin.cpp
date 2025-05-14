/* 
* Pin.cpp
*
* Created: 25-10-2024 12:39:50
* Author: VVCE
*/

#include "Pin.h"

Pin::Pin(const Pin &pin)
{
	this->port = pin.port;
	this->position = pin.position;
	this->direction = pin.direction;
}

Pin::Pin(IOPORT port, uint8 position, IODIRECTION direction)
{
	this->port = port;
	this->position = position;
	SetDirection(direction);
}

void Pin::SetDirection(IODIRECTION direction)
{
	this->direction = direction;
	switch(port)
	{
		case IOPORTB:	if(direction == INPUT)
							DDRB &= ~(1 << position);
						else
							DDRB |= (1 << position);
						break;
		case IOPORTC:	if(direction == INPUT)
							DDRC &= ~(1 << position);
						else
							DDRC |= (1 << position);
						break;
		case IOPORTD:	if(direction == INPUT)
							DDRD &= ~(1 << position);
						else
							DDRD |= (1 << position);
						break;	
	}
}

void Pin::Set()
{
	switch(port)
	{
		case IOPORTB:	PORTB |= (1 << position); break;
		case IOPORTC:	PORTC |= (1 << position); break;		
		case IOPORTD:	PORTD |= (1 << position); break;
	}
}

void Pin::Clear()
{
	switch(port)
	{
		case IOPORTB:	PORTB &= ~(1 << position); break;
		case IOPORTC:	PORTC &= ~(1 << position); break;
		case IOPORTD:	PORTD &= ~(1 << position); break;
	}
}

void Pin::Toggle()
{
	switch(port)
	{
		case IOPORTB:	PORTB ^= (1 << position); break;
		case IOPORTC:	PORTC ^= (1 << position); break;
		case IOPORTD:	PORTD ^= (1 << position); break;
	}
}

uint8 Pin::Read()
{
	uint8 data;
	switch(port)
	{
		case IOPORTB:	data = PINB & (1 << position) ? 0x01: 0x00; break;
		case IOPORTC:	data = PINC & (1 << position) ? 0x01: 0x00; break;
		case IOPORTD:	data = PIND & (1 << position) ? 0x01: 0x00; break;
	}
	return data;	
}