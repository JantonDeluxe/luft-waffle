#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc; // Zugriff auf RTC

void setup() {

  // Serial-Setup
  Serial.begin(115200);
  delay(100);
  Serial.println("");
  Serial.println("Serial gestartet!");

  if (! rtc.begin()) { // Keine Uhr entdeckt
    Serial.println("Echtzeituhr fehlt");
    // Fehlerbehandlung
  }

  if (! rtc.isrunning()) { // Uhr schon gesetzt?
    Serial.println("RTC bisher noch nicht gesetzt!");
    // => Initialisiere Zeit und Datum auf Datum/Zeit des Host-PCs
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime jetzt = rtc.now();

  Serial.print(jetzt.year(), DEC);
  Serial.print('/');
  Serial.print(jetzt.month(), DEC);
  Serial.print('/');
  Serial.print(jetzt.day(), DEC);
  Serial.print("     ");
  Serial.print(jetzt.hour(), DEC);
  Serial.print(':');
  Serial.print(jetzt.minute(), DEC);
  Serial.print(':');
  Serial.print(jetzt.second(), DEC);
  Serial.println();
}
