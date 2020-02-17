/* Höhenmesser 2.0

  Projektseite:
  -------------
  https://jantondeluxe.github.io


  Hardware:
  ---------
  Board: WEMOS D1 mini pro V1.0
  Altimeter: Bosch BMP180
  Display: GM009605 OLED
  D1 mini Data logger shield mit DS1307 RTC


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
#include <Wire.h>
#include <FS.h>
#include <SFE_BMP180.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SD.h>
#include <RTClib.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Header
#include "StartPage.h"
#include "ChartPage.h"
#include "AboutPage.h"


// Display-Eigenschaften definieren
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1 // -1, da kein Reset-Pin vorhanden


// Objekte
SFE_BMP180 pressure;
RTC_DS1307 RTC;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ESP8266WebServer server(80);

// Name und Passwort WLAN oder Access Point
const char* ssid = "Janky";
const char* password = "6zhnJI9ol.";


// Kalibrierung: Anzahl der Messungen
const int measurements = 100;

// Globale Variablen
double highest;
double P;
double h;
double Temp;
double v;
double a;
double S1;
double S2;
double deltaS;
double del = 0;
double timer = 200;
double lowestV;

bool startstop = false;

float T0;
float deltaT;
float Array[measurements];
float P0 = 0.0;

char status;

String data;




// Setup
void setup() {

  // Serial-Setup
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("Serial gestartet!");


  // I2C-Setup
  Wire.begin();
  Serial.println("I2C gestartet!");


  // Display-Setup
  if (display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    {
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.cp437(true);          // font
      display.setCursor(0, 0);
      Serial.println("Display gestartet!");
    }
  }
  else
  {
    Serial.println("Display nicht gefunden!");
    while (1);
  }

  drawLoadingscreen1();


  // Dateisystem starten
  if (SPIFFS.begin())
  {
    Serial.println("SPIFFS gestartet!");
  }
  else
  {
    Serial.println("SPIFFS nicht gestartet!");
    display.clearDisplay();
    display.print("SPIFFS nicht gestartet!");
    delay(1000);
    display.clearDisplay();
    while (1);
  }

  drawLoadingscreen2();


  // RTC-Setup
  if (RTC.begin())
    Serial.println("RTC gestartet!");
  else
  {
    Serial.println("RTC nicht gestartet!");
    display.clearDisplay();
    display.print("RTC nicht gestartet!");
    delay(1000);
    display.clearDisplay();
    while (1);
  }

  if (! RTC.isrunning()) {
    Serial.println("RTC bisher noch nicht gesetzt!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  drawLoadingscreen3();


  //Sensor-Setup
  if (pressure.begin())
    Serial.println("BMP180 gestartet!");
  else
  {
    Serial.println("BMP180 fehlt!");
    display.clearDisplay();
    display.print("BMP180 fehlt!");
    delay(1000);
    display.clearDisplay();
    while (1);
  }

  drawLoadingscreen4();


  // Basisdruck
  calculateBasePressure();
  
  Serial.println("Ausgangsdruck berechnet!");
  drawLoadingscreen5();


  // WLAN-Verbindung
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  drawLoadingscreen6();

  Serial.println("");
  Serial.print("Verbunden mit: ");
  Serial.println(ssid);

  drawLoadingscreen7();


  // Webserver-Setup
  server.on("/", handleRoot);
  server.on("/start", handleStart);
  server.on("/stopp", handleStopp);
  server.on("/chart", handleChart);
  server.on("/about", handleAbout);
  server.on("/calibrate", handleCalibration);
  server.on("/readData", handleData);
  server.onNotFound(handleWebRequests);

  server.begin();

  Serial.println("HTTP-Server gestartet!");
  Serial.print("IP: ");
  /* Serial.println(WiFi.softAPIP()); */
  Serial.println(WiFi.localIP());

  drawLoadingscreen8();

  drawLoadingscreen9();

  drawLoadingscreen9();

  drawLoadingscreen10();

  drawSplashscreen();
  delay(1500);
  display.clearDisplay();
}





void loop() {

  // Zeitmessung starten
  T0 = millis();

  /*// Uhrzeit anzeigen
    DateTime now = RTC.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println(")");
  */

  // Webserver
  server.handleClient();

  // Druck messen
  P = getPressure();

  // Ausgangsstrecke
  S1 = h;

  // Höhenunterschied
  h = pressure.altitude(P, P0);

  // Streckenberechnung
  S2 = h;
  deltaS = S2 - S1;

  // Maximum
  if (h > highest) highest = h;
  if (v < lowestV) lowestV = v;

  // Temperatur messen
  status = pressure.startTemperature();
  delay(status);
  status = pressure.getTemperature(Temp);

  // Werte anzeigen
  anzeige();

  // Mögliche Verzögerung
  delay(del);

  // Zeitmessung stoppen
  deltaT = millis() - T0;
  deltaT = deltaT / 1000;

  // Geschwindigkeit und Beschleunigung ausrechnen
  v = deltaS / deltaT;
  a = (2 * deltaS) / (deltaT * deltaT);

  // Messung gestartet
  if (startstop == true) {
    timer = timer - 1;
    if (timer == 0) {
      startstop = false;
    }
  }

  //if (a > 20)
  //  timer = 600

/*
  double t = millis() / 1000;
  String teil1 = String(String(t) + ";");
  String teil2 = String(teil1 + String(h));
  String teil3 = String(teil2 + ";");
  String teil4 = String(teil3 + String(v));
  String teil5 = String(teil4 + ";");
  String teil6 = String(teil5 + String(a));
  String teil7 = String(teil6 + ";");
  String teil8 = String(teil7 + String(highest));
  String teil9 = String(teil8 + ";");
  String teil10 = String(teil9 + String(Temp));

  data = data + teil10;

  Serial.println(data);
  */

}
