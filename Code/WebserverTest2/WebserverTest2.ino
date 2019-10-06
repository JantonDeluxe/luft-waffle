#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>       

ESP8266WebServer server(80);          // Webserverport auf 80 setzten (Standardport für Webserver)

const char *ssid = "Hoehenmesser";    // ssid festlegen
const char *password = "BoschBMP180"; // Passwort festlegen

const int test = 2;

void setup() {
  Serial.begin(115200);                 // Datenübertragung starten
  delay(10);
  Serial.println('\n');
  WiFi.softAP(ssid, password);          // AccessPoint starten mit ssid und Passwort 
  Serial.println("AccessPoint gestartet!");         
  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());      // IP-Adresse ausgeben

  server.on("/", HTTP_GET, handleRoot); // Funktion handleRoot ausführen, bei GET request nach "/" 
  server.on("/test", HTTP_POST, handleTest);
  server.onNotFound(handleNotFound);    // Funktion handleNotFound ausführen, bei request nach unbekannter URI
  server.begin();                       // Start: auf HTTP requests warten
  Serial.println("HTTP server gestartet!"); 
}

void loop() {
 server.handleClient();                  // dauerhaft auf HTTP requests warten
}

void handleRoot() {                  // HTTP status 200 und Website schicken
  server.send(200, "text/html", "<!DOCTYPE html>\"<html>\"<head>\"<title>Hoehenmesser</title>\"</head>\"<body>\"<p>Hier koennte ihre Werbung stehen!</p>\"</body>\"<form action=\"/test\" method=\"POST\"><input type=\"submit\" value=\"toggle test\"></form>\"</html>");
}

void handleTest() {                          // If a POST request is made to URI /test
  digitalWrite(test,!digitalRead(test));     // Change the state of test
  Serial.println(test);
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleNotFound(){               // HTTP status 404 schicken
  server.send(404, "text/plain", "404: Not found"); 
}
