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

Wir haben uns also dafür entschieden, ein hochauflösenderes Display statt den 7-Segmentanzeigen und ein Board mit WLAN und mehr Speicherplatz zu verwenden. Das Display ist nun ein No-Name-OLED-Display aus China und das neue Board ein [D1 mini Pro](https://wiki.wemos.cc/products:d1:d1_mini_pro) von WEMOS Electronics.

#### 21. August<a name="7"></a>
Zuhause haben wir die Aufgaben 1 bis 4 von StarlogoTNG erfolgreich abgeschlossen. 

In der Stunde haben wir angefangen den Laptop für unser Projekt einzurichten:
- Laptop in iSurf registriert
- [Arduino IDE](https://www.arduino.cc/en/Guide/Windows) installiert
- [D1 mini Pro Hardware Package](https://github.com/esp8266/Arduino) über die Arduino IDE installiert (_Voreinstellungen_ -> _zusätzliche Boardverwalter-URLs_ -> Link einfügen)
- [D1 mini Pro-Treiber](https://wiki.wemos.cc/downloads) installiert

Ebenfalls haben wir Zielsetzungen für den Höhenmesser aufgestellt. Der alte Höhenmesser konnte nur über das mitgelieferte Example-Sketch die aktuelle und maximale Höhe messen und eine von beiden anzeigen. Wenn möglich soll der neue Höhenmesser mehr können:
1. aktuelle Höhe auf Display anzeigen
2. maximale Höhe möglichst auf unter 1 Meter genau auf Display anzeigen
3. Temperatur und Druckwerte auf Display anzeigen
4. Daten auf Webserver anzeigen
5. Geschwindigkeit und Beschleunigung ausrechnen
6. Flugverlauf grafisch darstellen

#### 22. August<a name="8"></a>
Heute haben wir den Höhenmsser (ein [Bosch BMP 180-Sensor](https://www.sparkfun.com/products/retired/11824)) mit Hilfe des [Sparkfun-Tutorials](https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-/all) mit dem Mikrocontroller auf einem Breadboard verkabelt. Dann wollten wir das Example-Sketch auf den Mikrocontroller laden, was leider nicht funktioniert hat:
```
esptool.FatalError: Timed out waiting for packet headed

```
Deshalb haben wir statt der neuen Universal Windows Platform App aus dem Microsoft Store die Arduino IDE diesmal als normales Windows-Programm (über den .exe Installer) installiert, was das Problem aber nicht behoben hat. Sicherheitshalber haben wir deshalb den D1-Treiber ebenfalls neu installiert und weiter nach dem Fehler gesucht.

Parallel haben wir dieses Unterrichtstagebuch fortgeführt.

#### 27. August<a name="9"></a>
Heute haben wir endlich den Fehler gefunden, warum unser Board nicht mit der Arduino IDE kommunizieren konnte: Wir hatten vergessen, das Board engültig zu installieren. Das geht in der Arduino IDE unter _Werkzeug_e -> _Board_ -> _Boardverwalter_ -> Suche “ESP8266” (der ESP8266 ist der auf unserem Board verbaute Mikrocontroller) -> _Installieren_. Zusätzlich muss man für unser spezielles Board weitere Zusatzeinstellungen in den prefrences.txt hinzufügen, wofür es glücklicherweise eine [Vorlage](https://arduino-projekte.info/wp-content/uploads/2017/07/boards.txt) gibt. Dann muss man die Arduino IDE nur noch neustarten und das Board unter Werkzeuge -> Board auswählen. Sehr geholfen haben uns bei der Installation diesese beiden Tutorials: 
- (https://arduino-projekte.info/installation-eps8266-modul-wie-z-b-wemos/)
- (https://arduino-projekte.info/installation-wemos-d1-mini-lite-wemos-d1-mini-pro/)

Wenn wir diesen Schritt nicht vergessen hätten, hätte das Hochladen des Programms trotzdem nicht funktioniert, da auf der Hersteller-Website des D1 eine veraltete Boardverwalter-URL angegeben war, was uns nur durch Zufall aufgefallen ist. 

#### 28.August<a name="10"></a>
An diesem Tag haben wir begonnen den Arduino zu programmieren und die ersten Daten auszulesen. Dazu haben wir ein Beispielprogramm hochgeladen von der Github-Website des Herstellers und dann die Höhe auf 0 gesetzt. Allerdings hat der Arduino die Höhe dann als Konstante angezeigt.

Heute haben wir den Zeitraum gemessen, indem die Messwerte unseren Start-Schwellwert von 2 Metern übersteigen. Der Zeitraum beträgt 18 Minuten. Um sicher zugehen, dass die Abweichung nicht zu groß wird, wird spätestens alle 10 Minuten eine Rekalibrierung vorgenommen wird, um einen neuen Nullwert zu errechnen.


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
