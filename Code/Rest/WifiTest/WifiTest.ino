#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;

char NetworkStatus;
const char* ssid = "Hoehenmesser";
const char* password = "BoschBMP180";

void setup() {
  Serial.begin(9600);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Janky", "6zhnJI9ol.");

  NetworkStatus = wifiMulti.run();
  Serial.println("Mit Netzwerk verbinden...");
  delay(5000);
  Serial.println(NetworkStatus);

  if (NetworkStatus = WL_CONNECTED) {
    Serial.print("WLAN");
  }
  else
  {
    WiFi.softAP(ssid, password);
    Serial.print("AP");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
