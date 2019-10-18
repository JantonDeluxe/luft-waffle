// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>  

#include "index.h"


// Webserver-Port setzen
ESP8266WebServer server(80);          // Webserverport auf 80 setzten (Standardport für Webserver)

// Name und Passwort Access Point
const char *ssid = "H&ouml;henmesser";    // ssid festlegen
const char *password = "***REMOVED***"; // Passwort festlegen

float height = 2.43;

//Setup
void setup() {

  //Datenübertragung
  Serial.begin(115200);
  delay(100);
  Serial.println("");

  // AccessPoint
  WiFi.softAP(ssid, password);         
  Serial.println("AccessPoint gestartet!");     

  //Webserver
  server.on("/", handleRoot); // Funktion handleRoot ausführen, bei GET request nach "/" 
  server.on("/data", handleData);
  server.onNotFound(handleNotFound);    // Funktion handleNotFound ausführen, bei request nach unbekannter URI
  server.begin();
  Serial.println("HTTP-Server gestartet!"); 
  Serial.print("IP: ");
  Serial.print(WiFi.softAPIP());
}

  
// Hauptcode
void loop() {
  
  // Webserver
  server.handleClient();
}
      
//Webserver

void handleData(){
  float height = 
  server.send(200, height);
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}


void handleNotFound(){               // HTTP status 404 schicken
  server.send(404, "text/plain", "404: Not found");
}
