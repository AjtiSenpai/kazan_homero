

#include <SPI.h>
#include <Wire.h>
#define I2C_ADDRESS 0x3C
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include "MAX6675.h"

#define analogPin  A7 
#define beta 3950
#define resistance 100 

SSD1306AsciiWire oled;

float temperature = 0;
MAX6675           myMAX6675(5);

void setup() {
  Wire.begin(); 
  Serial.begin(9600);
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.setFont(System5x7);
  oled.clear();
myMAX6675.begin();

  while (myMAX6675.getChipID() != MAX6675_ID)
  {
    oled.setCursor(0, 0);
    oled.print("MAX6675 error");
    delay(5000);
  }

  oled.clear();
  oled.print("MAX6675 OK");
  delay(2000);

  if   (myMAX6675.detectThermocouple() == true) Serial.println(F("K-Thermocouple is connected to MAX6675 terminals 'T+' & 'T-'"));
  else                                          Serial.println(F("K-Thermocouple is broken, unplugged or 'T-' terminal is not grounded"));
}

void loop() {

  long a = analogRead(analogPin);
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  delay(200);
  temperature = myMAX6675.getTemperature();
  
  oled.clear();
  oled.println(F("Víz:  "));
  oled.println(tempC);
  oled.println("  C");
  
  oled.setCursor(0,31);
  oled.println("Füst: "); 
  if (temperature != MAX6675_ERROR) oled.print(temperature, 1);
  else                              oled.print(F("xx"));       
  oled.println("  C");  
  delay(2000);

  
}
