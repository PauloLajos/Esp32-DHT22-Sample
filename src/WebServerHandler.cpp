#include "WebServerHandler.h"
#include <WiFi.h>
#include <WebServer.h>
#include <FS.h>
#include <SPIFFS.h>
#include "SensorHandler.h"
#include "WiFiConfig.h"
#include <vector>

WebServer server(SERVERPORT);

String loadFile(const char* path) {
  Serial.print("Fájl megnyitása: ");
  Serial.println(path);

  if (!SPIFFS.exists(path)) {
    Serial.println("Nincs ilyen fájl a SPIFFS-ben!");
    return String("Hiba: nincs index.html a SPIFFS-ben!");
  }

  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.println("Nem sikerült megnyitni a fájlt!");
    return String("Hiba: fájl megnyitási hiba.");
  }

  String content = file.readString();
  file.close();
  Serial.println("Fájl sikeresen beolvasva!");
  return content;
}

void handleRoot() {
  File file = SPIFFS.open("/index.html", "r");
  if (!file) {
    server.send(500, "text/plain", "index.html not found");
    return;
  }
  server.streamFile(file, "text/html");
  file.close();
}

void handleData() {
  auto& data = getDailyData();
  String json = "[";
  for (size_t i = 0; i < data.size(); i++) {
    json += "{";
    json += "\"time\":" + String(data[i].timestamp) + ",";
    json += "\"temperature\":" + String(data[i].temperature, 1) + ",";
    json += "\"humidity\":" + String(data[i].humidity, 1);
    json += "}";
    if (i < data.size() - 1) json += ",";
  }
  json += "]";
  server.send(200, "application/json", json);
}

void handleNotFound() {
  Serial.print("Ismeretlen kérés: ");
  Serial.println(server.uri());
  server.send(404, "text/plain", "404: " + server.uri());
}

void setupWebServer() {
  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS csatolás sikertelen!");
    return;
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Csatlakozás WiFi-re");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nCsatlakozva: " + WiFi.localIP().toString());

  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/favicon.ico", []() { server.send(204); }); // favicon tiltás
  server.onNotFound(handleNotFound);   // <<< EZ FONTOS!

  server.begin();
  Serial.println("Webserver fut a " + String(SERVERPORT) + " porton.");
}

void handleWebServer() {
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 3000) {
    lastRead = millis();
    readSensor(); // 3 másodpercenként olvasás
  }
  server.handleClient();
}