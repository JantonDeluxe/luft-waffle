/* Webserver-Funktionen*/

// Hauptseite
void handleRoot() {
  Serial.println("Website abgerufen.");
  String q = StartPage;
  server.send(200, "text/html", q);
}

// Messung starten, Redirect auf ChartPage
void handleStart() {
  startstop = true;
  highest = 0;
  Serial.println("Messung gestartet!");
  server.sendHeader("Location", "/chart");
  server.send(303);
}

// Messung stoppen, Redirect auf StartPage
void handleStopp() {
  timer = 200;
  startstop = false;
  Serial.println("Messung gestoppt!");
  server.sendHeader("Location", "/");
  server.send(303);
}

// Chart-Seite
void handleChart() {
  String r = ChartPage;
  Serial.println("Chart aufgerufen");
  server.send(200, "text/html", r);
}

// About-Seite
void handleAbout() {
  String s = AboutPage;
  Serial.println("About-Seite aufgerufen");
  server.send(200, "text/html", s);
}

// Manuelle Kalibrierung mit Redirect auf StartPage
void handleCalibration() {
  calculateBasePressure();
  Serial.println("Ausgangsdruck neu berechnet!");
  server.sendHeader("Location", "/");
  server.send(303);
}

// Datenübertragung
void handleData() {
  double t = millis() / 1000;
  String teil1 = String(String(t) + ";");
  String teil2 = String(teil1 + String(h));
  String teil3 = String(teil2 + ";");
  String teil4 = String(teil3 + String(v));
  String teil5 = String(teil4 + ";");
  String teil6 = String(teil5 + String(a));
  String teil7 = String(teil6 + ";");
  String teil8 = String(teil7 + String(highest));
  String teil9 = String(teil8 + ";");
  String teil10 = String(teil9 + String(Temp));
  String teil11 = String(teil10 + ";");
  String kombi = String(teil11 + String(timer / 100 / 6));
  server.send(200, "text/plain", kombi);
}

// Unbekannte URI: Datei oder Error 404
void handleWebRequests() {
  if (loadFromSpiffs(server.uri())) return;
  String message = "File Not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println(message);
}

// dataType der angeforderten Datei bestimmen
bool loadFromSpiffs(String path) {
  String dataType = "text/plain";
  if (path.endsWith("/")) path += "index.htm";

  if (path.endsWith(".src")) path = path.substring(0, path.lastIndexOf("."));
  else if (path.endsWith(".html")) dataType = "text/html";
  else if (path.endsWith(".htm")) dataType = "text/html";
  else if (path.endsWith(".css")) dataType = "text/css";
  else if (path.endsWith(".js")) dataType = "application/javascript";
  else if (path.endsWith(".png")) dataType = "image/png";
  else if (path.endsWith(".gif")) dataType = "image/gif";
  else if (path.endsWith(".jpg")) dataType = "image/jpeg";
  else if (path.endsWith(".ico")) dataType = "image/x-icon";
  else if (path.endsWith(".xml")) dataType = "text/xml";
  else if (path.endsWith(".pdf")) dataType = "application/pdf";
  else if (path.endsWith(".zip")) dataType = "application/zip";
  File dataFile = SPIFFS.open(path.c_str(), "r");
  if (server.hasArg("download")) dataType = "application/octet-stream";
  if (server.streamFile(dataFile, dataType) != dataFile.size()) {
  }

  dataFile.close();
  return true;
}
