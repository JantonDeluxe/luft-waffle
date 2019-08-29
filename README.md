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
In unserer ersten Informatikstunde haben wir uns überlegt, was für Projekte wir gerne machen würden und auf code.org mit einem Einsteiger-Kurs angefangen.

#### 14. August 2019<a name="4"></a>
Heute haben wir einen [GitHub-Account](https://github.com/JantonDeluxe), ein [Repository](https://github.com/JantonDeluxe/luft-waffle) und unsere [Website](https://jantondeluxe.github.io/luft-waffle/) erstellt, die wir über den [editor](https://github.com/JantonDeluxe/luft-waffle/edit/master/README.md) bearbeiten.
Für die Website haben wir das [Jekyll](https://jekyllrb.com/)-Theme Minimal benutzt.

#### 15. August 2019<a name="5"></a>
Heute haben wir uns für einen Wasserraketen-Höhenmesser als Projekt entschieden und dafür angefangen, uns mit dem [Arduino](https://arduino.cc) und der Programmiersprache [C++](https://de.m.wikipedia.org/wiki/C%2B%2B) auseinanderzusetzten. Ebenfalls haben wir Links in unsere Website eingefügt und uns abgesprochen, wer was zu nächster Stunde vorbereitet.

#### 20. August 2019<a name="6"></a>
Heute haben wir genaue Ziele festgelegt und den Laptop in iSurf angemeldet. Außerdem haben wir nach vier Jahren unseren [alten Höhenmesser](http://jan.krummrey.de/2015/09/13/hoehenmesser-fur-unsere-wasserrakete/) wieder ausgepackt. 
Aktueller Stand: Der Höhenmesser kalibriert sich am Anfang durch 100faches Messen und rechnet damit seinen Nullwert aus. Von diesem Nullwert wird die relative Höhe berechnet und in Echtzeit auf das Display ausgegeben.

<details>
 <summary>Programm von 2015</summary>
 
```

*/

// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>
#include <SSD1306Ascii.h>
#include <SSD1306AsciiWire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":
SFE_BMP180 pressure;

// OLED Display Objekt
// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C
#define OPTIMIZE_I2C   1
SSD1306AsciiWire oled;

double baseline; // baseline pressure
double highest;
double lowest;
double T;
double noise = 8.0;

void setup()
{
  Wire.begin();
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
  oled.set400kHz();
  oled.setFont(font5x7);
  oled.clear();

  // Initialize the sensor (it is important to get calibration values stored on the device).
  oled.set2X();
  oled.println("REBOOT");
  oled.set1X();

  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin())
    oled.println("BMP180 gefunden");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    oled.println("BMP180 fehlt!");
    while (1); // Pause forever.
  }

  char status;
  // Get the baseline pressure:
  // and temperature

  baseline = getPressure();
  status = pressure.startTemperature();
  delay(status);

  status = pressure.getTemperature(T);
  if (status != 0)
  {
    oled.clear();
    oled.print(baseline);
    oled.print(" mb");

    oled.print("    ");
    oled.print(T);
    oled.println(" C");

    oled.setCursor(0, 3);
    oled.print("Hoehe:");
    oled.setCursor(0, 5);
    oled.print("Max:");

    oled.setCursor(0, 7);
    oled.print("13:19:42   06.05.2017");

  }
}

void loop()
{
  double a, P;

  // Get a new pressure reading:

  P = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

  a = pressure.altitude(P, baseline);

  if (a < lowest) lowest = a;

  if (a > highest) highest = a;

  
  oled.set2X();
  oled.setCursor(40, 2);
  if (a >= 0.0) oled.print(" "); // add a space for positive numbers
  oled.print(a);
  oled.print("m");

  oled.setCursor(40, 4);
   if (highest >= 0.0) oled.print(" "); // add a space for positive numbers
  oled.print(highest);
  oled.print("m");

/*  oled.set1X();
  oled.print("Min: ");
  oled.println(lowest);
*/
 
  //  delay(500);
}


double getPressure()
{
  char status;
  double T, P, p0, a;

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

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return (P);
        }
        else oled.println("error retrieving pressure measurement\n");
      }
      else oled.println("error starting pressure measurement\n");
    }
    else oled.println("error retrieving temperature measurement\n");
  }
  else oled.println("error starting temperature measurement\n");
}

```
 </details>
 

#### 21. August<a name="7"></a>
Zuhause haben wir die Aufgaben 1 bis 4 von StarlogoTNG erfolgreich abgeschlossen.
Heute haben wir den Zeitraum gemessen, indem die Messwerte unseren Start-Schwellwert von 2 Metern übersteigen. Der Zeitraum beträgt 18 Minuten. Um sicher zugehen, dass die Abweichung nicht zu groß wird, wird spätestens alle 10 Minuten eine Rekalibrierung vorgenommen wird, um einen neuen Nullwert zu errechnen.

#### 22. August<a name="8"></a>
Heute haben wir mit Hilfe des [Sparkfun-Tutorials](https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/all) zu unserem Bosch BMP 180-Sensor angefangen Programme auf den Mikrokontroller zu laden.
Das hat leider nicht funktioniert, da auf unserem Laptop die falschen Treiber installiert waren. Deshalb haben wir sowohl die Arduino IDE, als auch den D1 Mini Pro-Treiber neu installiert, was das Problem nicht behoben hat.

´´´

esptool.FatalError: Timed out waiting for packet header

ˋˋˋ

#### 27. August< name="9"></a>
Heute haben wir endlich den Fehler gefunden, warum unser Board nicht mit der Arduino IDE kommunizieren konnte. Zunächst mussten wir in der Arduino IDE den unseren Mikrocontroller ESP8266 einstellen und die Voreinstellungen für unser Board verändern. Das hat dann endlich geklappt.

#### 28.August< name="10"></a>
An diesem Tag haben wir begonnen den Arduino zu programmieren und die ersten Daten auszulesen. Dazu haben wir ein Beispielprogramm hochgeladen von der Github-Website des Herstellers und dann die Höhe auf 0 gesetzt. Allerdings hat der Arduino die Höhe dann als Konstante angezeigt.

#### 29.August< name="11"></a>
Am Donnerstag haben wir das Problem mit der Höhe behoben und die Auslesung der Daten so programmiert, dass sie uns geordnet angezeigt werden.

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
