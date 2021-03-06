/* Höhenmesser
  
  Projektseite:
  -------------
  https://jantondeluxe.github.io


  Hardware:
  ---------
  Board: WEMOS D1 mini pro V1.0
  Altimeter: Bosch BMP180
  Display: GM009605 OLED


  Disclaimer:
  -----------
  Basiert teilweise auf dem Sketch BMP180_altitude_example aus der SFE_BMP180-Library:
  V10 Mike Grusin, SparkFun Electronics 10/24/2013
  V1.1.2 Updates for Arduino 1.6.4 5/2015

  Basiert teilweise auf dem Tutorial "ESP8266 data logging with real time graphs" auf
  https://circuits4you.com/2019/01/11/esp8266-data-logging-with-real-time-graphs/


  Danke an Nick Lamprecht für seine Hilfe mit Java Skript!
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

// I2C-Adresse OLED
#define I2C_ADDRESS 0x3C

// Objekte
SFE_BMP180 pressure;
SSD1306AsciiWire oled;

// Webserver-Port setzen
ESP8266WebServer server(80);

// Name und Passwort Access Point
const char *ssid = "";  
const char *password = ""; 

// Kalibrierung: Anzahl der Messungen
const int messungen = 100;

// Globale Variablen
double highest;
double lowest;
char status;
double P;
double T;
double a;
double* pointereins = &T;
double* pointerzwei = &a;

float Array[messungen];
float ausgangsdruck = 0.0;


//Setup
void setup(void) {

  //Datenübertragung
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("Datenübertragung gestartet!");
  
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
    Serial.println("BMP180 gestartet!");
  else
  {
    Serial.println("BMP180 fehlt!");
    while (1);
  }

  // WLAN-Verbindung
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Verbunden mit:");
  Serial.println(ssid);

  // Webserver-Setup
  server.on("/", handleRoot);
  server.on("/readData", handleData);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("HTTP-Server gestartet!"); 
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  // Kalibrierung
  for (int i = 0; i < messungen; i++)
  {
    Array[i] = getPressure();
  }
  
  for (int i = 0; i < messungen; i++)
  {
    ausgangsdruck = ausgangsdruck + Array[i];
  }
  
  ausgangsdruck = ausgangsdruck / messungen;

  // statische Teile der Höhenanzeigen
  oled.setCursor(0, 3);
  oled.print("Hoehe:");
  oled.setCursor(0,5);
  oled.print("Max:");

  }


  // Hauptcode
  void loop(void) {

    // Webserver
    server.handleClient();
    
    // Druck messen
    P = getPressure();

    // Temperatur messen
    status = pressure.startTemperature();
    delay(100);
    status = pressure.getTemperature(T);

    // Höhenunterschied
    a = pressure.altitude(P, ausgangsdruck);

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

    // Druckanzeige
    oled.setCursor(0, 0);
    oled.print(getPressure());
    oled.print(" mbar");

    // Temperaturanzeige
    oled.setCursor(79, 0);
    if (a >= 0.0) oled.print(" ");
    oled.print(*pointereins);
    oled.println(" C");

    // IP-Adresse anzeigen
    oled.setCursor(0, 7);
    oled.print("IP: ");
    oled.print(WiFi.localIP());
    
    delay(333);
  }
  

// Webserver
void handleRoot() {
  String s = MAIN_page;
  server.send(200, "text/html", s);
}

void handleData(){
  double d = *pointerzwei;
  double t = millis() / 1000;
  String teil = String(String(t) + ";");
  String kombi = String(teil + String(d));
  server.send(200, "text/plain", kombi);
}

void handleNotFound(){              
  server.send(404, "text/plain", "404: Not found"); 
}


// Funktion getPressure
double getPressure()
{
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
        else Serial.println("Fehler beim Erhalten des Drucks");
      }
      else Serial.println("Fehler beim Starten der Druckmessung");
    }
    else Serial.println("Fehler beim Erhalten der Temperatur");
  }
  else Serial.println("Fehler beim Starten der Temperaturmessung");
}
