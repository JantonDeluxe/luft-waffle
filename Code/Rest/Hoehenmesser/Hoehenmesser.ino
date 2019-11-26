/* Höhenmesser

  Hardware:
  ---------
  Board: WEMOS D1 mini pro V1.0
  Altimeter: Bosch BMP180
  Display: GM009605 OLED


  Fehlercodes:
  ------------
  1 - Fehler beim Erhalten des Drucks
  2 - Fehler beim Starten der Druckmessung
  3 - Fehler beim Erhalten der Temperatur
  4 - Fehler beim Starten der Temperaturmessung

  Basiert teilweise auf dem Sketch BMP180_altitude_example aus der SFE_BMP180-Library:
  V10 Mike Grusin, SparkFun Electronics 10/24/2013
  V1.1.2 Updates for Arduino 1.6.4 5/2015

  Basiert teilweise auf dem Sketch WiFiAccessPoint aus der ESP8266WebServer-Library:
  Copyright (c) 2015, Majenko Technologies
*/

// Libraries
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Header
#include "index.h"

// Objekte
SFE_BMP180 pressure;
SSD1306AsciiWire oled;

// I2C-Adresse OLED
#define I2C_ADDRESS 0x3C

// Name und Passwort Access Point
const char *ssid = "Hoehenmesser";  
const char *password = "***REMOVED***"; 

// Variablen
double baseline;
double highest;
double lowest;
double T;
double a;
double* pointer = &a;

// Webserver-Port setzen
ESP8266WebServer server(80);



//Setup
void setup(void) {

  //Datenübertragung
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  
  //Display-Setup
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  
  Serial.println("Display gestartet!"); 

  oled.clear();
  oled.set2X();
  oled.println("START");
  oled.set1X();
  delay(500);
  oled.clear();

  //Sensor-Setup
  if (pressure.begin())
    Serial.println("BMP180 gefunden!");
  else
  {
    Serial.println("BMP180 fehlt!");
    while (1);
  }

  // Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point gestartet!"); 

  // Webserver-Setup
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("HTTP-Server gestartet!"); 
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());
  
  // baseline-Druck messen
  baseline = getPressure();       // Genauer wäre: 100 getPressure-Werte und dann den Durchschnitt davon als baseline

  // baseline-Druck anzeigen
  oled.print(baseline);
  oled.print(" mbar");
 
  // statische Teile der Höhenanzeigen
  oled.setCursor(0, 3);
  oled.print("Hoehe:");
  oled.setCursor(0,5);
  oled.print("Max:");
 
  }


  // Hauptcode
  void loop(void) {

    // Variablen
    double a, P;
    char status;

    // Webserver
    server.handleClient();
    
    // Druck messen
    P = getPressure();

    // Temperatur messen
    status = pressure.startTemperature();
    delay(100);
    status = pressure.getTemperature(T);

    // Höhenunterschied
    a = pressure.altitude(P, baseline);

    // Maximalwerte
    if (a < lowest) lowest = a;

    if (a > highest) highest = a;

    // Höhenunterschied anzeigen
    oled.set2X();
    oled.setCursor(40, 2);               
    if (a >= 0.0) oled.print(" ");      
    oled.print(a);
    oled.print("m");

    // Maximum anzeigen
    oled.setCursor(40, 4);               
    if (highest >= 0.0) oled.print(" ");
    oled.print(highest);
    oled.print("m");
    oled.set1X();

    // Temperaturanzeige
    oled.setCursor(80, 0);
    oled.print(T);
    oled.println(" C");

    // IP-Adresse anzeigen
    oled.setCursor(0, 7);
    oled.print("IP: ");
    oled.print(WiFi.softAPIP());
    
    delay(500);
  }
  

// Webserver
void handleRoot() {
 String s = MAIN_page;
 server.send(200, "text/html", s);
}

void handleData(){
  double d = *pointer ;
  String data = String(d);
  server.send(200, "text/plane", data);
}

void handleNotFound(){              
  server.send(404, "text/plain", "404: Not found"); 
}


// Funktion getPressure()
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
      
      // Druck messen mit Genauigkeitsstufe 3
      status = pressure.startPressure(3);
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
