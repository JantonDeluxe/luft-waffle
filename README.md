# Hallo!
## Inhaltsverzeichnis
***

[Projektbeschreibung](#1)

[Unterrichtstagebuch](#2)

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[13. August](#3)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[14. August](#4)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[15. August](#5)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[20. August](#6)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[21. August](#6)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[22. August](#7)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[27. August](#8)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[27. August](#9)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[28. August](#10)
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[29. August](#11)

***

## Projektbeschreibung<a name="1"></a>

## Unterrichtstagebuch <a name="2"></a>

#### 13. August 2019<a name="3"></a>
In unserer ersten Informatikstunde haben wir uns überlegt, was für Projekte wir gerne machen würden und auf [code.org](https://code.org/) mit einem Einsteiger-Kurs angefangen.
Unsere Vorkenntnisse sind auf einfache Programmieraufgaben mit [Scratch](https://de.wikipedia.org/wiki/Scratch_(Programmiersprache)) im Rahmen des Jugendwettbewerbs Informatik beschränkt.
***
#### 14. August 2019<a name="4"></a>
Heute haben wir einen [GitHub-Account](https://github.com/JantonDeluxe), ein [Repository](https://github.com/JantonDeluxe/luft-waffle) und unsere [Website](https://jantondeluxe.github.io/luft-waffle/) erstellt, die wir über den [editor](https://github.com/JantonDeluxe/luft-waffle/edit/master/README.md) bearbeiten.
Für die Website benutzen wir vorläufig das [Jekyll](https://jekyllrb.com/)-Theme Minimal, sind aber noch auf der Suche nach einem besseren Theme.
***
#### 15. August 2019<a name="5"></a>
Heute haben wir uns für ein Arduino-Projekt entschieden und dafür angefangen, uns mit dem [Arduino](https://arduino.cc) und der Programmiersprache [C](https://de.wikipedia.org/wiki/C_(Programmiersprache)) auseinanderzusetzten. Ebenfalls haben wir Links in unsere Website eingefügt und weiterüberlegt, wie wir am besten lernen und was für ein Projekt genau wir umsetzen wollen.
***
#### 20. August 2019<a name="6"></a>
Am Wochenende hatten wir uns dafür entschieden, einen Höhenmesser für Wasserraketen zu bauen. Diese Art von Höhenmesser kostet off-the-shelf mindestens 50 €, weshalb wir Geld sparen und den Sensor selbst bauen wollen. Basieren tut der Höhenmesser auf einem Versuch, den ich, Anton, vor vier Jahren mit meinem Vater unternommen habe. 

Dieser [alte Höhenmesser](http://jan.krummrey.de/2015/09/13/hoehenmesser-fur-unsere-wasserrakete/) hatte jedoch einige Schwachstellen, weshalb wir ihn nie zuende gebaut haben: 
- durch die zwei 7-Segment-Anzeigen konnte immer nur eine Information mit maximal zwei Ziffern angezeigt werden 
- es konnten keine Daten ausgelesen werden, da der Arduino nano sich bei USB Verbindungen resettet
- es konnten keine längeren Messreihen wie Flugverläufe gespeichert werden, da der Speicher dafür nicht ausgereicht hat
- der Arduino nano hat kein WLAN, weshalb man sich immer per USB-Kabel verbinden muss, was schwer möglich ist, wenn der Sensor in einer Rakete eingebaut ist

![Alter Höhenmesser](https://i1.wp.com/jan.krummrey.de/wp-content/uploads/2015/09/11951281_10153345040958153_9145140276330392700_n.jpg)

Wir haben uns also dafür entschieden, ein hochauflösenderes Display statt den 7-Segmentanzeigen und ein Board mit WLAN und mehr Speicherplatz zu verwenden. Das Display ist nun ein 128×64 Pixel GM009605 OLED-Display mit SSD1306-Controller aus China und das neue Board ein [D1 mini Pro V1.0](https://wiki.wemos.cc/products:retired:d1_mini_pro_v1.1.0) mit ESP8266-Mikrocontroller von WEMOS Electronics.
***
#### 21. August<a name="7"></a>
Zuhause haben wir die Aufgaben 1 bis 4 von StarlogoTNG erfolgreich abgeschlossen. 

In der Stunde haben wir angefangen den Laptop für unser Projekt einzurichten:
- Laptop in iSurf registriert
- [Arduino IDE](https://www.arduino.cc/en/Guide/Windows) installiert
- [D1 mini Pro Hardware Package](https://github.com/esp8266/Arduino) über die Arduino IDE installiert 

  (_Voreinstellungen_ -> _zusätzliche Boardverwalter-URLs_ -> Link einfügen)

- [D1 mini Pro-Treiber](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers) installiert

Ebenfalls haben wir Zielsetzungen für den Höhenmesser aufgestellt. Der alte Höhenmesser sollte über das zum Sensor gehörende Example-Sketch (siehe unten) die aktuelle messen und auf den Anzeigen darstellen. Zusätzlich konnte die maximale Höhe berechnet werden und durch das Blinken der im Arduino eingebauten LED ausgegeben werden. Das funktioniert, ist aber nicht sehr "nutzerfreundlich". Der Code ist leider in den vier Jahren verloren gegangen, basierte aber bis auf das Berechnen des Maximalwerts und dem Blinken der LED auf dem Example Sketch: 

<details><summary>Example Sketch</summary>
<p>

Diesen Beispiel-Code findet man in der Arduino IDE unter 

_Datei_ -> _Beispiele_ -> _BMP180_ -> _Examples_ -> _BMP180_altitude_example_

```
/* SFE_BMP180 altitude example sketch

This sketch shows how to use the Bosch BMP180 pressure sensor
as an altimiter.
https://www.sparkfun.com/products/11824

Like most pressure sensors, the BMP180 measures absolute pressure.
Since absolute pressure varies with altitude, you can use the pressure
to determine your altitude.

Because pressure also varies with weather, you must first take a pressure
reading at a known baseline altitude. Then you can measure variations
from that pressure

Hardware connections:

- (GND) to GND
+ (VDD) to 3.3V

(WARNING: do not connect + to 5V or the sensor will be damaged!)

You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:

Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3

Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V

Have fun! -Your friends at SparkFun.

The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/

Our example code uses the "beerware" license. You can do anything
you like with this code. No really, anything. If you find it useful,
buy me a beer someday.

V10 Mike Grusin, SparkFun Electronics 10/24/2013
V1.1.2 Updates for Arduino 1.6.4 5/2015

*/

// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

double baseline; // baseline pressure

void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  // Get the baseline pressure:
  
  baseline = getPressure();
  
  Serial.print("baseline pressure: ");
  Serial.print(baseline);
  Serial.println(" mb");  
}

void loop()
{
  double a,P;
  
  // Get a new pressure reading:

  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

  a = pressure.altitude(P,baseline);
  
  Serial.print("relative altitude: ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a,1);
  Serial.print(" meters, ");
  if (a >= 0.0) Serial.print(" "); // add a space for positive numbers
  Serial.print(a*3.28084,0);
  Serial.println(" feet");
  
  delay(500);
}


double getPressure()
{
  char status;
  double T,P,p0,a;

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
```
</p>
</details>

Wenn möglich soll der neue Höhenmesser mehr können:
1. aktuelle Höhe auf Display anzeigen
2. maximale Höhe möglichst auf unter 1 Meter genau auf Display anzeigen
3. Temperatur und Druckwerte auf Display anzeigen
4. Daten auf Webserver anzeigen
5. Geschwindigkeit und Beschleunigung ausrechnen
6. Flugverlauf grafisch darstellen
***
#### 22. August<a name="8"></a>
Heute haben wir den Höhenmsser (ein [Bosch BMP 180-Sensor](https://www.sparkfun.com/products/retired/11824)) mit Hilfe des [Sparkfun-Tutorials](https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/all) mit dem Mikrocontroller auf einem Breadboard verkabelt.

Übersicht; welcher Pin wohin ;)

Dann wollten wir zum Testen das Example-Sketch auf den Mikrocontroller laden, was leider nicht funktioniert hat:
```
esptool.FatalError: Timed out waiting for packet headed

```
Deshalb haben wir statt der neuen Universal Windows Platform App aus dem Microsoft Store die Arduino IDE diesmal als normales Windows-Programm (über den .exe Installer) installiert, was das Problem aber nicht behoben hat. Sicherheitshalber haben wir deshalb den D1-Treiber ebenfalls neu installiert und weiter nach dem Fehler gesucht.

Parallel haben wir dieses Unterrichtstagebuch fortgeführt.
***
#### 27. August<a name="9"></a>
Heute haben wir endlich den Fehler gefunden, warum unser Board nicht mit der Arduino IDE kommunizieren konnte: Wir hatten vergessen, das Board engültig zu installieren. Das geht in der Arduino IDE unter

_Werkzeuge_ -> _Board_ -> _Boardverwalter_ -> Suche “ESP8266” (der ESP8266 ist der auf unserem Board verbaute Mikrocontroller) -> _Installieren_. 

Zusätzlich muss man für unser spezielles Board weitere Zusatzeinstellungen in den prefrences.txt hinzufügen, wofür es glücklicherweise eine [Vorlage](https://arduino-projekte.info/wp-content/uploads/2017/07/boards.txt) gibt. Dann muss man die Arduino IDE nur noch neustarten und unter 

_Werkzeuge_ -> _Board_ -> "LOLIN(WEMOS) D1 mini Pro" auswählen.

Sehr geholfen haben uns bei der Installation diesese beiden Tutorials: 
- (https://arduino-projekte.info/installation-eps8266-modul-wie-z-b-wemos/)
- (https://arduino-projekte.info/installation-wemos-d1-mini-lite-wemos-d1-mini-pro/)

Wenn wir diesen Schritt nicht vergessen hätten, hätte das Hochladen des Programms trotzdem nicht funktioniert, da auf der Hersteller-Website des D1 eine veraltete Boardverwalter-URL angegeben war, was uns nur durch Zufall aufgefallen ist. 
***
#### 28.August<a name="10"></a>
Heute konnten wir endlich testen, ob wir den Sensor richtig verkabelt haben. Dafür haben wir das oben erwähnte Example Sketch auf den D1 hochgeladen und die Daten ausgelsen. Das funktioniert so:

In Text-Form: _Werkzeuge_ -> _Serieller Monitor_

![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Serieller%20Monitor.png?raw=true)

Als Graph: _Werkzeuge_ -> _Serieller Plotter_

(Diese Funktion ist neu, vor vier Jahren brauchten wir für die graphische Darstellung noch ein extra Processing-Skript.)

![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Serieller%20Plotter.png?raw=true)

_Blau: Höhe in Meter_
_Rot: Höhe in feet_

Die Verkabelung ist also korrekt. Aus Spaß haben wir dann noch das zweite Example Sketch, das eigentlich für Wettermessungen gedacht ist ausprobiert: 

<details><summary>Example Sketch 2</summary>
<p>

Diesen Beispiel-Code findet man in der Arduino IDE unter 

_Datei_ -> _Beispiele_ -> _BMP180_ -> _Examples_ -> _SFE_BMP180_example_

```
/* SFE_BMP180 library example sketch

This sketch shows how to use the SFE_BMP180 library to read the
Bosch BMP180 barometric pressure sensor.
https://www.sparkfun.com/products/11824

Like most pressure sensors, the BMP180 measures absolute pressure.
This is the actual ambient pressure seen by the device, which will
vary with both altitude and weather.

Before taking a pressure reading you must take a temparture reading.
This is done with startTemperature() and getTemperature().
The result is in degrees C.

Once you have a temperature reading, you can take a pressure reading.
This is done with startPressure() and getPressure().
The result is in millibar (mb) aka hectopascals (hPa).

If you'll be monitoring weather patterns, you will probably want to
remove the effects of altitude. This will produce readings that can
be compared to the published pressure readings from other locations.
To do this, use the sealevel() function. You will need to provide
the known altitude at which the pressure was measured.

If you want to measure altitude, you will need to know the pressure
at a baseline altitude. This can be average sealevel pressure, or
a previous pressure reading at your altitude, in which case
subsequent altitude readings will be + or - the initial baseline.
This is done with the altitude() function.

Hardware connections:

- (GND) to GND
+ (VDD) to 3.3V

(WARNING: do not connect + to 5V or the sensor will be damaged!)

You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:

Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3

Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V

Have fun! -Your friends at SparkFun.

The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/

Our example code uses the "beerware" license. You can do anything
you like with this code. No really, anything. If you find it useful,
buy me a beer someday.

V10 Mike Grusin, SparkFun Electronics 10/24/2013
V1.1.2 Updates for Arduino 1.6.4 5/2015

*/

// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters

void setup()
{
  Serial.begin(9600);
  Serial.println("REBOOT");

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}

void loop()
{
  char status;
  double T,P,p0,a;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:
  
  Serial.println();
  Serial.print("provided altitude: ");
  Serial.print(ALTITUDE,0);
  Serial.print(" meters, ");
  Serial.print(ALTITUDE*3.28084,0);
  Serial.println(" feet");
  
  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("temperature: ");
      Serial.print(T,2);
      Serial.print(" deg C, ");
      Serial.print((9.0/5.0)*T+32.0,2);
      Serial.println(" deg F");
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print("absolute pressure: ");
          Serial.print(P,2);
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");

          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          Serial.print("relative (sea-level) pressure: ");
          Serial.print(p0,2);
          Serial.print(" mb, ");
          Serial.print(p0*0.0295333727,2);
          Serial.println(" inHg");

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.

          a = pressure.altitude(P,p0);
          Serial.print("computed altitude: ");
          Serial.print(a,0);
          Serial.print(" meters, ");
          Serial.print(a*3.28084,0);
          Serial.println(" feet");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  delay(5000);  // Pause for 5 seconds.
}
```
</p>
</details>

Dabei haben wir die vorgegebene Höhe (Boulder, Colorado: 1655 Meter) auf 0 gesetzt, um die gesuchte relative Höhe zu erhalten:
```
#define ALTITUDE 0.0
```
Danach wurde uns allerdings erstmal trotz Bewegung dauerhaft die Höhe 0 angezeigt:

![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Example%20Sketch%202.png?raw=true)

Letzlich lag das daran, dass die Höhe nur in ganzen Zahlen ausgegeben wurde und die Bewegungen kleiner als 1 Meter waren, weshalb keine neue Höhe angezeigt wurde.

Mit dem ersten Example Skecth haben wir dann den Zeitraum gemessen, in dem die Messwerte eine Ungenauigkeit von 2 Metern übersteigen. Der Zeitraum beträgt 18 Minuten. Um sicher zugehen, dass die Abweichung nicht zu groß wird, sollte also etwa alle 10 Minuten eine Rekalibrierung vorgenommen werden, um einen neuen Nullwert zu errechnen.
***
#### 29.August<a name="11"></a>
Heute haben wir mit Hilfe dieses  das OLED-Display in Betrieb genommen.

Übersicht welcher Pin wohin

![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Zusammengesteckt%20auf%20Breadboard1.jpeg?raw=true)

Nachdem das Display verkabelt war mussten wir für unser testprogramm die nun die benötigten Libraries installieren:
```
#include <Wire.h>             // Arduino-Standard-Library für die Datenübertragung (I2C)
#include <SSD1306Ascii.h>     // Library für die Buchstabendarstellung auf dem Display
#include <SSD1306AsciiWire.h> // Library für die Übertragung auf das OLED-Display 
```
Damit die Library SSD1306AsciiWire funktioniert muss man ein Objekt mit dem Namen "oled" initialisieren:
```
SSD1306AsciiWire oled;    
```
Um das Display später auch ansteuern zu können, muss man die I2C-Adresse des Displays herausfinden. Dabei geholfen hat uns dieses [Tutorial](https://www.instructables.com/id/Monochrome-096-i2c-OLED-display-with-arduino-SSD13/). Für diese Aufgabe gibt es nämlich den [I2C-Scanner](https://playground.arduino.cc/Main/I2cScanner/), den man auf das Board lädt und der einem dann die Adresse des Displays ausgibt. In unserem Fall ist das die Adresse 0x3C (vorher hatten wir den Sensor abgesteckt, damit uns nur die Adresse des Displays angezeigt wird). 

![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/I2c-Scan.png?raw=true)

Also haben wir die Adresse gesetzt:
```
#define I2C_ADDRESS 0x3C 
```
Jetzt kann das Setup beginnen:
```
void setup() {
Wire.begin();                                // Wire-Protokoll initialisieren (Beginn der Datenübertragung)
  oled.begin(&Adafruit128x64, I2C_ADDRESS);  // Display initialisieren
  oled.set400kHz();                          // Datenübertragungsrate setzen
  oled.setFont(font5x7);                     // Fontgröße setzen
  oled.clear();                              // Display leeren (sicherheitshalber)
  oled.set2X();                              // Größere Buchstaben
  oled.println("START");                     // START schreiben
  oled.set1X();                              // Buchstaben wieder auf Normalgröße
}
```
Das eigentliche Programm besteht dann nur darin, "Hallo!" in großen Buchstaben anzuzeigen:
```
void loop() {
 oled.set2X();                              // Größere Buchstaben
  oled.println("Hallo!");                   // "Hallo!" schreiben
}
```
Und das hat funktioniert:
![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/hallo!.jpeg?raw=true)

<details><summary>Ganzes Test-Programm</summary>
<p>
  
```
#include <Wire.h>
#include <SSD1306Ascii.h> 
#include <SSD1306AsciiWire.h>

SSD1306AsciiWire oled;

#define I2C_ADDRESS 0x3C

void setup() {
 Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  oled.clear();
  oled.set2X();               
  oled.println("START");
  oled.set1X();   
}

void loop() {
 oled.set2X();
  oled.println("Hallo!");
}
```
</p>
</details>

***
#### 11. September<a name="12"></a>
Heute haben wir angefangen, Daten vom Höhenmesser auf dem Display anzuzeigen. Dafür haben wir die beiden Testprogramme ersteinmal kombiniert übersetzt und etwas kommentiert:

<details><summary>Kombiniertes Programm</summary>
<p>
  
```
/* Höhenmesser

Fehlercodes:

1 - Fehler beim Erhalten des Drucks
2 - Fehler beim Starten der Druckmessung
3 - Fehler beim Erhalten der Temperatur
4 - Fehler beim Starten der Temperaturmessung

 */

// Libraries
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h> 
#include <SSD1306AsciiWire.h>

// Objekte
SFE_BMP180 pressure;   
SSD1306AsciiWire oled;

// Adresse des Displays auf 0x3C setzen
#define I2C_ADDRESS 0x3C

// Variable
double baseline;

//Setup
void setup() {
  
  //Display-Setup
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  
  oled.clear();
  oled.set2X();               
  oled.println("START");
  oled.set1X();
  delay(4000);
  oled.clear();

  //Sensor-Setup
  if (pressure.begin())
    oled.println("BMP180 gefunden!");
  else
  {
    oled.println("BMP180 fehlt!");
    while(1);
  }

  delay(4000);
  
  // baseline-Druck messen
  baseline = getPressure();

  //baseline-Druck anzeigen
  oled.clear();
  oled.println("baseline-Druck: ");
  oled.println(baseline);
  oled.println(" mb");  

  delay(4000);
}

// Hauptcode
void loop() {
  double a,P;
  
  // Druck messen
  P = getPressure();

  //Höhenunterschied anzeigen
  a = pressure.altitude(P,baseline);
  
  oled.clear();
  oled.println("Hoehe: ");
  if (a >= 0.0) Serial.print(" ");
  oled.println(a,1);
  oled.println("Meter");
 
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

```
</p>
</details>

<details><summary>Display-Fotos</summary>
<p>
  
![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Start.jpeg?raw=true)
![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/BMP.jpeg?raw=true)
![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Druck.jpeg?raw=true)
![alt text](https://github.com/JantonDeluxe/luft-waffle/blob/master/Bilder/Hoehe.jpeg?raw=true)

</p>
</details>

***
#### 12. September<a name="13"></a
Heute haben wir zunächst die fehlermeldungen getestet und dann Fehlercodes aufgestellt, da die angezeigten Fehlermeldungen zu lang für das Display waren. Dabei haben wir gleich die Beschreibung unseres Codes oben erweitert:
  
```
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
```
Danach haben wir angefangen, die maximale Höhe zu berechnen. Das tun wir wie beim alten Höhenmesser mit Hilfe zweier neuer Variablen:
```
double highest;     // Max-Druck
double lowest;      // Min-Druck
```
Wenn der gemessene Höhenunterschied (Variable a) kleiner als der kleinste bzw. größer als der größte Wert ist, wird dieser Wert als höchster (highest) bzw. kleinster (lowest) Wert gesetzt:
```
  if (a < lowest) lowest = a;

  if (a > highest) highest = a;
```
Den Minimumwert wollen wir nur aus Interesse haben, der Maximumwert soll jedoch angezeigt werden:
```
oled.setCursor(0, 4);                  // Cursor unter die Höhenanzeige bewegen
  if (highest >= 0.0) oled.print(" "); // Leerzeichen, wenn positive Zahl
oled.print(highest);                   
oled.print("m");
```
Das ganze funktioniert sehr gut, sieht aber nicht gut aus. Deshalb haben wir angefangen, uns zu überlegen, wie ein besseres Layout aussehen könnte.
***
#### 24. September<a name="14"></a>
Heute haben wir für das neue Layout für die Temperatur-Anzeige angefangen. Dafür haben wir eine neue Variable deklariert:
```
double T;           // Temperatur
```
In unseren ersten Versuchen wurde erstmal nur die Temperatur zum Start-Zeitpunkt angezeigt. Das wäre akzeptabel, aber nicht das, was wir eigentlich wollen.
Dann haben wir versucht mit Hilfe von Pointern die Temperatur aus der Definition von getPressure() zu verwenden, was elegant, aber für uns auch sehr zeitaufwändig war: Kurz vor Ende der Stunde waren wir fertig, das ganze hat jedoch nicht funktioniert hat, weil die Library dafür nicht ausgelegt ist.
***
#### 25. September<a name="15"></a>
Heute haben wir das Temperatur-Problem auf eine relativ einfache Weise gelöst. Statt T aus der Definition von getPressure() direkt zu verwenden, haben wir die Temperaturmessung aus getPressure() kopiert und vereinfacht. Zunächst haben wir die Variable status als char deklariert:
```
char status;
```
Und dann die Temperaturmessung von unten kopiert und auf's nötigste reduziert:
```
status = pressure.startTemperature();
delay(100);
status = pressure.getTemperature(T);
```
Die Temperatur wird jetzt provisorisch unter dem Maximum angezeigt:
```
// baseline-Druck anzeigen
oled.setCursor(0, 5);          // Cursor unter die Maximumanzeige bewegen
    if (T >= 0.0) oled.print(" "); // Leerzeichen, wenn positive Zahl
    oled.print(T);
    oled.print(" C");
```
***
#### 26. September<a name="16"></a>
Heute haben wir das neue Layout gebaut. Der baseline-Druck steht weiterhin oben rechts, jetzt aber in einer Reihe und mit der Einheit mbar statt mb:
```
oled.clear();
oled.print(baseline);
oled.print(" mbar");
```
Darunter kommen, immernoch im setup, die Teile der Anzeige, die sich nicht verändern - also "Hoehe:", "Max:" und Platz für sonstigen Text:
```
// statische Teile der Höhenanzeigen
 oled.setCursor(0, 3);
 oled.print("Hoehe:");
 oled.setCursor(0,5);
 oled.print("Max:");

 // Sonstiger Text
 oled.setCursor(0, 7);
 oled.print("blablabla");
```

Die veränderlichen Teile der Anzeige stehen im Hauptteil des Codes:
```
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
```
Die Anzeige sieht jetzt so aus:

*** 

You can use the  to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run  to rebuild the pages in your site, from the content in your Markdown files.

### Markdown

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/JantonDeluxe/luft-waffle/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
