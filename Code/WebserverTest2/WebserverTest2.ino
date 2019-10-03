#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>  
#include <ESP8266mDNS.h>     

ESP8266WebServer server(80);          // Webserverport auf 80 setzten (Standard)

const char *ssid = "Hoehenmesser";    // ssid festlegen
const char *password = "BoschBMP180"; // Passwort festlegen

void setup() {
  Serial.begin(115200);               // Datenübertragung starten
  WiFi.softAP(ssid, password);        // AccessPoint starten mit ssid und Passwort          
  Serial.println(WiFi.softAPIP());    // IP-Adresse ausgeben
  
   if (!MDNS.begin("hoehenmesser")) { //  mDNS responder für hoehenmesser.local starten
    Serial.println("Fehler beim Starten des mDNS responders");
  }
  Serial.println("mDNS responder gestartet");

  server.on("/", handleRoot);         // Funktion handleRoot starten, wenn der client nach "/" fragt
  server.onNotFound(handleNotFound);  // Funktion handleNotFound starten, wenn der client nach einem unbekannten URI fragt
  server.begin();
  Serial.println("HTTP server gestartet!"); 
}

void loop() {
 server.handleClient();              // auf HTTP requests warten
}

void handleRoot() {                  // HTTP status 200 und Website schicken
  server.send(200, "text/html", "<!DOCTYPE html>\"<html>\"<head>\"<title>Hoehenmesser</title>\"</head>\"<body>\"<p>Hier koennte ihre Werbung stehen!</p>\"</body>\"</html>");
}

void handleNotFound(){               // HTTP status 404 schicken
  server.send(404, "text/plain", "404: Not found"); 
}
