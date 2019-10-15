/* Höhenmesser

Fehlercodes:

1 - Fehler beim Erhalten des Drucks
2 - Fehler beim Starten der Druckmessung
3 - Fehler beim Erhalten der Temperatur
4 - Fehler beim Starten der Temperaturmessung

 */

// Libraries
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h> 
#include <SSD1306AsciiWire.h>

// Objekte
SFE_BMP180 pressure;   
SSD1306AsciiWire oled;

// Adresse des Displays auf 0x3C setzen
#define I2C_ADDRESS 0x3C

// Variable
double baseline;

//Setup
void setup() {
  
  //Display-Setup
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  
  oled.clear();
  oled.set2X();               
  oled.println("START");
  oled.set1X();
  delay(4000);
  oled.clear();

  //Sensor-Setup
  if (pressure.begin())
    oled.println("BMP180 gefunden!");
  else
  {
    oled.println("BMP180 fehlt!");
    while(1);
  }

  delay(4000);
  
  // baseline-Druck messen
  baseline = getPressure();

  //baseline-Druck anzeigen
  oled.clear();
  oled.println("baseline-Druck: ");
  oled.println(baseline);
  oled.println(" mb");  

  delay(4000);
}

// Hauptcode
void loop() {
  double a,P;
  
  // Druck messen
  P = getPressure();

  //Höhenunterschied anzeigen
  a = pressure.altitude(P,baseline);
  
  oled.clear();
  oled.println("Hoehe: ");
  if (a >= 0.0) Serial.print(" ");
  oled.println(a,1);
  oled.println("Meter");
 
  delay(500);
}


// Funktion getPressure() definieren
double getPressure()
{
  // Variablen
  char status;
  double T,P,p0,a;
  
  // Temperatur messen
  status = pressure.startTemperature();
  if (status != 0)
  {
    // Warten bis Messung fertig
    delay(status);

     // Temperatur erhalten
    status = pressure.getTemperature(T);
    if (status != 0)
    {
      
      // Druck messen
      status = pressure.startPressure(3);      // Höchste von 3 Genauigkeits-Stufen der Library
      if (status != 0)
      {
        // Warten bis Messung fertig
        delay(status);

        //Druck erhalten
        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else oled.println("Fehler 1");
      }
      else oled.println("Fehler 2");
    }
    else oled.println("Fehler 3");
  }
  else oled.println("Fehler 4");
}
