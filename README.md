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

#### 14. August 2019<a name="4"></a>
Heute haben wir einen [GitHub-Account](https://github.com/JantonDeluxe), ein [Repository](https://github.com/JantonDeluxe/luft-waffle) und unsere [Website](https://jantondeluxe.github.io/luft-waffle/) erstellt, die wir über den [editor](https://github.com/JantonDeluxe/luft-waffle/edit/master/README.md) bearbeiten.
Für die Website benutzen wir vorläufig das [Jekyll](https://jekyllrb.com/)-Theme Minimal, sind aber noch auf der Suche nach einem besseren Theme.

#### 15. August 2019<a name="5"></a>
Heute haben wir uns für ein Arduino-Projekt entschieden und dafür angefangen, uns mit dem [Arduino](https://arduino.cc) und der Programmiersprache [C](https://de.wikipedia.org/wiki/C_(Programmiersprache)) auseinanderzusetzten. Ebenfalls haben wir Links in unsere Website eingefügt und weiterüberlegt, wie wir am besten lernen und was für ein Projekt genau wir umsetzen wollen.

#### 20. August 2019<a name="6"></a>
Am Wochenende hatten wir uns dafür entschieden, einen Höhenmesser für Wasserraketen zu bauen. Diese Art von Höhenmesser kostet off-the-shelf mindestens 50 €, weshalb wir Geld sparen und den Sensor selbst bauen wollen. Basieren tut der Höhenmesser auf einem Versuch, den ich, Anton, vor vier Jahren mit meinem Vater unternommen habe. 

Dieser [alte Höhenmesser](http://jan.krummrey.de/2015/09/13/hoehenmesser-fur-unsere-wasserrakete/) hatte jedoch einige Schwachstellen, weshalb wir ihn nie zuende gebaut haben: 
- durch die zwei 7-Segment-Anzeigen konnte immer nur eine Information mit maximal zwei Ziffern angezeigt werden 
- es konnten keine Daten ausgelesen werden, da der Arduino nano sich bei USB Verbindungen resettet
- es konnten keine längeren Messreihen wie Flugverläufe gespeichert werden, da der Speicher dafür nicht ausgereicht hat
- der Arduino nano hat kein WLAN, weshalb man sich immer per USB-Kabel verbinden muss, was schwer möglich ist, wenn der Sensor in einer Rakete eingebaut ist

![Alter Höhenmesser](https://i1.wp.com/jan.krummrey.de/wp-content/uploads/2015/09/11951281_10153345040958153_9145140276330392700_n.jpg)

Wir haben uns also dafür entschieden, ein hochauflösenderes Display statt den 7-Segmentanzeigen und ein Board mit WLAN und mehr Speicherplatz zu verwenden. Das Display ist ein No-Name-OLED-Display aus China und das neue Board ein [D1 mini Pro](https://wiki.wemos.cc/products:d1:d1_mini_pro) von WEMOS Electronics.

#### 21. August<a name="7"></a>
Zuhause haben wir die Aufgaben 1 bis 4 von StarlogoTNG erfolgreich abgeschlossen.
Heute haben wir den Zeitraum gemessen, indem die Messwerte unseren Start-Schwellwert von 2 Metern übersteigen. Der Zeitraum beträgt 18 Minuten. Um sicher zugehen, dass die Abweichung nicht zu groß wird, wird spätestens alle 10 Minuten eine Rekalibrierung vorgenommen wird, um einen neuen Nullwert zu errechnen.

#### 22. August<a name="8"></a>
Heute haben wir mit Hilfe des [Sparkfun-Tutorials](https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/all) zu unserem Bosch BMP 180-Sensor angefangen Programme auf den Mikrokontroller zu laden.
Das hat leider nicht funktioniert, da auf unserem Laptop die falschen Treiber installiert waren. Deshalb haben wir sowohl die Arduino IDE, als auch den D1 Mini Pro-Treiber neu installiert, was das Problem nicht behoben 
hat.

```
esptool.FatalError: Timed out waiting for packet headed

```


#### 27. August<a name="9"></a>
Heute haben wir endlich den Fehler gefunden, warum unser Board nicht mit der Arduino IDE kommunizieren konnte. Zunächst mussten wir in der Arduino IDE den unseren Mikrocontroller ESP8266 einstellen und die Voreinstellungen für unser Board verändern. Das hat dann endlich geklappt.

#### 28.August<a name="10"></a>
An diesem Tag haben wir begonnen den Arduino zu programmieren und die ersten Daten auszulesen. Dazu haben wir ein Beispielprogramm hochgeladen von der Github-Website des Herstellers und dann die Höhe auf 0 gesetzt. Allerdings hat der Arduino die Höhe dann als Konstante angezeigt.

#### 29.August<a name="11"></a>
Am Donnerstag haben wir das Problem mit der Höhe behoben und die Auslesung der Daten so programmiert, dass sie uns geordnet angezeigt werden.

#### 11. September<a name="12"></a>
Arduino-Tutorial

#### 12. September<a name="13"></a
 Arduino-Tutorial

#### 24. September<a name="14"></a>
neues Layout für die Anzeige

#### 25. September<a name="15"></a>
Pointer für Temperatur ausprobiert, damit nicht nur die Anfangstemperatur angezeigt wird

#### 26. September<a name="16"></a>
Pointer nicht möglich, weil das nicht mit den Funktionen aus der Library zusammenpasst

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
