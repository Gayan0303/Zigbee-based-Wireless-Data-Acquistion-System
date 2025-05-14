#define F_CPU 1000000UL
#define BAUDRATE 2400
#define UBRVALUE (F_CPU / (BAUDRATE * 16UL)) - 1

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "Pin.h"
#include "I2C.h"
#include "GY302.h"
#include "AHT10.h"
#include "MQ135.h"
#include "BareLCD.h"  

void SetUART() 
{
	UBRRH = (uint8_t)(UBRVALUE >> 8);
	UBRRL = (uint8_t)UBRVALUE;

	UCSRB = (1 << RXEN) | (1 << TXEN);
	UCSRC = (1 << URSEL) | (1 << USBS) | (3 << UCSZ0);  
}


void SendData(char data)
{
	while (!(UCSRA & (1 << UDRE)));
	UDR = data;
}


void WriteString(char str[])
{
	int i = 0;
	while (str[i] != '\0')
	{
		SendData(str[i]);
		i++;
	}
}

int main(void)
{
	
	Pin scl(IOPORTD, 6, OUTPUT);
	Pin sda(IOPORTD, 7, OUTPUT);

	I2C i2c(&sda, &scl);

	
	GY302 lightSensorObj(&i2c);
	AHT10 aht10SensorObj(&i2c);
	MQ135 mqObj;

	
	BareLCD lcd(&i2c);
	lcd.begin();  

	
	SetUART();

	while (1)
	{
		float temperature, humidity, lightIntensity;
		aht10SensorObj.ReadTemperatureAndHumidity(&temperature, &humidity);
		lightIntensity = lightSensorObj.ReadLightIntensity();
		float PPM = mqObj.getPPM();

		
		char buffer[100];
		int tempInt = (int)(temperature * 10);
		int humInt = (int)(humidity * 10);
		int lightInt = (int)(lightIntensity * 10);
		int ppmInt = (int)(PPM * 10);

		sprintf(buffer, "T:%d.%dC,H:%d.%d%%LI:%d.%d,PPM:%d.%d\r\n",
		tempInt / 10, tempInt % 10,
		humInt / 10, humInt % 10,
		lightInt / 10, lightInt % 10,
		ppmInt / 10, ppmInt % 10);

		WriteString(buffer);   
		lcd.print(buffer);     

		_delay_ms(1000);
	}
}
