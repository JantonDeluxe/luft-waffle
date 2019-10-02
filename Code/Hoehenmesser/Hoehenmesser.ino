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

  Basiert teilweise auf dem BMP180_altitude_example des Höhenmessers:
  V10 Mike Grusin, SparkFun Electronics 10/24/2013
  V1.1.2 Updates for Arduino 1.6.4 5/2015
*/

// Libraries
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Objekte
SFE_BMP180 pressure;
SSD1306AsciiWire oled;

// Adresse des Displays auf 0x3C setzen
#define I2C_ADDRESS 0x3C

// Beschreibung
#ifndef APSSID
#define APSSID "Hoehenmesser"
#define APPSK  "***REMOVED***"
#endif

// Variable
double baseline;
double highest;
double lowest;
double T;

const char *ssid = APSSID;
const char *password = APPSK;

// Webserver-Port setzen
ESP8266WebServer server(80);

// wofür genau?
const int led = 13;

// Text schreiben
void handleRoot() {
  server.send(200, "text/plain", "Hoehenmesser"); //wie wechsel ich die Zeilen?
}

//Setup
void setup(void) {

  //Display-Setup
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);

  oled.clear();
  oled.set2X();
  oled.println("START");
  oled.set1X();
  delay(500);
  oled.clear();

  //Sensor-Setup
  if (pressure.begin())
    oled.println("BMP180 gefunden!");
  else
  {
    oled.println("BMP180 fehlt!");
    while (1);
  }

  delay(500);


 // baseline-Druck messen
  baseline = getPressure();

 // baseline-Druck anzeigen
 oled.clear();
 oled.print(baseline);
 oled.print(" mbar");

 // statische Teile der Höhenanzeigen
 oled.setCursor(0, 3);
 oled.print("Hoehe:");
 oled.setCursor(0,5);
 oled.print("Max:");

    
 delay(100);

  // Webserver-Setup
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
  }

  // Hauptcode
  void loop(void) {

    // Variablen
    double a, P;
    char status;

    // Webserver
    server.handleClient();
    MDNS.update();
    
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
    oled.setCursor(40, 2);               // Cursor bewegen
    if (a >= 0.0) oled.print(" ");       // Leerzeichen, wenn positive Zahl
    oled.print(a);
    oled.print("m");

    // Maximum anzeigen
    oled.setCursor(40, 4);               // Cursor unter die Höhenanzeige bewegen
    if (highest >= 0.0) oled.print(" "); // Leerzeichen, wenn positive Zahl
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
    oled.print(WiFi.localIP());
    
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
