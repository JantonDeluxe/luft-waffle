// Libraries
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>  
#include <FS.h>


// Webserver-Port setzen
ESP8266WebServer server(80);          // Webserverport auf 80 setzten (Standardport für Webserver)

// Name und Passwort Access Point
const char *ssid = "Hoehenmesser";    // ssid festlegen
const char *password = "***REMOVED***"; // Passwort festlegen



// Variablen
double OnOff;

//Setup
void setup() {

  OnOff = 0;

  //Datenübertragung
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  
  // AccessPoint
  WiFi.softAP(ssid, password);         
  Serial.println("AccessPoint gestartet!");     

  //Webserver
  server.on("/", HTTP_GET, handleRoot); // Funktion handleRoot ausführen, bei GET request nach "/" 
  server.on("/start", HTTP_POST, handleStart);
  server.on("/stopp", HTTP_POST, handleStopp);
  server.onNotFound(handleNotFound);    // Funktion handleNotFound ausführen, bei request nach unbekannter URI
  server.begin();
  Serial.println("HTTP-Server gestartet!"); 
  Serial.println("IP: ");
  Serial.println(WiFi.softAPIP());


  //SPIFFS
  if(SPIFFS.begin())
  {
    Serial.println("SPIFFS: OK!");
  }
  else
  {
    Serial.println("SPIFFS: Fehler!");
  }

  if(SPIFFS.format())
  {
    Serial.println("Formatierung: OK!");
  }
  else
  {
    Serial.println("Formatierung: Fehler!");
  }



}

  

// Hauptcode
void loop() {
  
  // Webserver
  server.handleClient();

}
      
//Webserver
void handleRoot() {                  // HTTP status 200 und Website schicken
  server.send(200, "text/html", "<!DOCTYPE html><html><head><title>Hoehenmesser</title></head><body><h1>Hoehenmesser</h1><p>Zum Starten Start druecken.</p></body><form action=\/start\ method=\POST\><input type=\submit\ value=\Start\></form><form action=\/stopp\ method=\POST\><input type=\submit\ value=\Stopp\></form></html>");
}

void handleStart() {                          // If a POST request is made to URI /knopf
  OnOff = 1;
  Serial.println(OnOff);
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleStopp() {
  OnOff = 0;
  Serial.println(OnOff);
  server.sendHeader("Location","/");
  server.send(303);
}

void handleNotFound(){               // HTTP status 404 schicken
  server.send(404, "text/plain", "404: Not found");
}
