/* Funktion anzeige()*/

void anzeige() {

  // Anzeige-Vorbereitung
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.cp437(true);          // font

  // statische Teile der Höhenanzeigen
  display.setCursor(0, 12);
  display.print("Hoehe:");
  display.setCursor(0, 32);
  display.print("Max:");

  // Höhenunterschied
  display.setTextSize(2);
  display.setCursor(40, 12);
  if (h >= 0.0) display.print(" ");
  display.print(h);
  display.print("m");

  // Maximum
  display.setCursor(40, 32);
  if (highest >= 0.0) display.print(" ");
  display.print(highest);
  display.print("m");
  display.setTextSize(1);

  // Druck
  display.setCursor(54, 0);
  display.print(getPressure());
  display.print(" mbar");

  // Temperatur
  display.setCursor(0, 0);
  display.print(Temp);
  display.println(" C ");

  // Geschwindigkeit
  display.setCursor(0, 56);
  display.print(lowestV);
  display.print(" m/s");

  // anzeigen
  display.display();
}
