#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);


void setup() 
{
  Serial.begin(2400);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Waiting for data");
}

void loop() 
{
  String receivedData = Serial.readStringUntil('\n');
  Serial.println("RX: \n" + receivedData);
  if (receivedData == "\n")
  {
    lcd.clear();
    lcd.setcursor(0,0);
    lcd.print(receivedData.substring(0,16);
    lcd.setCursor(0,1);
    if(receivedData.length() > 16)
    {
      lcd.print(receivedData.substring(16,32));      
    } 
  }
}
