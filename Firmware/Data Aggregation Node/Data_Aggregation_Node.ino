#include <Wire.h>
#include <SoftwareSerial.h>


SoftwareSerial Xbee(15,16);

void setup() 
{
  Xbee.begin(2400);
  Serial.begin(2400);
  Serial.println("Started....");
  
}

void loop() 
{

    String receivedData = Serial.readStringUntil('\n');  // Read until newline
    Serial.println("RX: \n" + receivedData);  // Optional: still log to Serial
    Xbee.println(receivedData);
}
