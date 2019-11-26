/* Funktion anzeige()*/

void anzeige() {
  
    // statische Teile der Höhenanzeigen
    oled.setCursor(0, 3);
    oled.print("Hoehe:");
    oled.setCursor(0,5);
    oled.print("Max:");

    // Höhenunterschied anzeigen
    oled.set2X();
    oled.setCursor(40, 2);               
    if (h >= 0.0) oled.print(" ");      
    oled.print(h);
    oled.print("m");

    // Maximum anzeigen
    oled.setCursor(40, 4);               
    if (highest >= 0.0) oled.print(" ");
    oled.print(highest);
    oled.print("m");
    oled.set1X();

    // Druckanzeige
    oled.setCursor(0, 0);
    oled.print(getPressure());
    oled.print(" mbar");

    // Temperaturanzeige
    oled.setCursor(79, 0);
    if (a >= 0.0) oled.print(" ");
    oled.print(T);
    oled.setCursor(115, 0);
    oled.println(" C");

    // IP-Adresse anzeigen
    oled.setCursor(0, 7);
    oled.print("IP: ");

   /* oled.print(WiFi.softAPIP());*/
    oled.print(WiFi.localIP());

   }
