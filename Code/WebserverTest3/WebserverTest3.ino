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


  Danke an Nick Lamprecht für die Hilfe mit Java Script!
*/

// Libraries
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h> 

// Header
#include "index.h"

// I2C-Adresse OLED
#define I2C_ADDRESS 0x3C

// Objekte
SFE_BMP180 pressure;
SSD1306AsciiWire oled;
ESP8266WebServer server(80);

// Name und Passwort WLAN oder Access Point
const char* ssid = "Hoehenmesser";  
const char* password = "***REMOVED***"; 

// Kalibrierung: Anzahl der Messungen
const int messungen = 100;

// Globale Variablen
double highest;
double lowest;
double P;
double a;
double T;


double* pointereins = &T;
double* pointerzwei = &a;

char status;

float Array[messungen];
float ausgangsdruck = 0.0;



//Setup
void setup(void) {

  // Serial-Setup
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("Serial gestartet!");

  // I2C-Setup
  Wire.begin();
  Serial.println("I2C gestartet!");

  //Display-Setup
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

/* // WLAN-Verbindung
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Verbunden mit: ");
  Serial.println(ssid);
*/

  // Access Point-Setup
  IPAddress local_IP(192,168,4,22);
  IPAddress gateway(192,168,4,9);
  IPAddress subnet(255,255,255,0);

  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("Access Point getstartet!");

  // Dateisystem starten
  if(SPIFFS.begin())
   {
     Serial.println("SPIFFS gestartet!");
   }
   else
   {
     Serial.println("SPIFFS nicht gestartet!");
     while (1);
    }

  // Webserver-Setup
  server.on("/", handleRoot);
  server.on("/readData", handleData);
  server.onNotFound(handleWebRequests);
  server.begin();

  Serial.println("HTTP-Server gestartet!"); 
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP()); 
/*
  Serial.println(WiFi.localIP());
*/
  
  // Basisdruck
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

    // Höhenunterschied
    a = pressure.altitude(P, ausgangsdruck);

    // Maximalwerte
    if (a < lowest) lowest = a;

    if (a > highest) highest = a;

    // Temperatur messen
    status = pressure.startTemperature();
    delay(100);
    status = pressure.getTemperature(T);

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

    oled.print(WiFi.softAPIP());
    
    /*
    oled.print(WiFi.localIP());
    */
    
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

void handleWebRequests(){
  if(loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " NAME:"+server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

bool loadFromSpiffs(String path){
  String dataType = "text/plain";
  if(path.endsWith("/")) path += "index.htm";
 
  if(path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if(path.endsWith(".html")) dataType = "text/html";
  else if(path.endsWith(".htm")) dataType = "text/html";
  else if(path.endsWith(".css")) dataType = "text/css";
  else if(path.endsWith(".js")) dataType = "application/javascript";
  else if(path.endsWith(".png")) dataType = "image/png";
  else if(path.endsWith(".gif")) dataType = "image/gif";
  else if(path.endsWith(".jpg")) dataType = "image/jpeg";
  else if(path.endsWith(".ico")) dataType = "image/x-icon";
  else if(path.endsWith(".xml")) dataType = "text/xml";
  else if(path.endsWith(".pdf")) dataType = "application/pdf";
  else if(path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }
 
  dataFile.close();
  return true;
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
