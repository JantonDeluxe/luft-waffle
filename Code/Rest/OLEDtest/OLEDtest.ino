#include <Wire.h>
#include <SSD1306Ascii.h> 
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire oled;

#define I2C_ADDRESS 0x3C

void setup() {
 Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  oled.clear();
  oled.set2X();               
  oled.println("START");
  oled.set1X();   
}

void loop() {
 oled.set2X();
  oled.println("Hallo!");
}
