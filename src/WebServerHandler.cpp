#include "WebServerHandler.h"
#include <WiFi.h>
#include "DHTSensor.h"
#include "wifi_config.h"

static WebServer* server = nullptr;   // dinamikusan inicializáljuk porttal

// HTML oldal
void handleRoot() {
  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset='utf-8'>
    <title>DHT WebServer</title>
    <style>
      body { font-family: Arial; margin: 20px; }
      h1 { color: #2c3e50; }
      .data { margin: 10px 0; font-size: 18px; }
    </style>
    <script>
      async function updateData() {
        let response = await fetch('/data');
        let json = await response.json();
        document.getElementById('status').innerText = json.status;
        document.getElementById('humidity').innerText = json.humidity + ' %';
        document.getElementById('tempC').innerText = json.tempC + ' °C';
        document.getElementById('tempF').innerText = json.tempF + ' °F';
        document.getElementById('heatC').innerText = json.heatC + ' °C';
        document.getElementById('heatF').innerText = json.heatF + ' °F';
      }
      setInterval(updateData, 3000);
      window.onload = updateData;
    </script>
  </head>
  <body>
    <h1>DHT22 mérési adatok</h1>
    <div class="data"><b>Status:</b> <span id="status">--</span></div>
    <div class="data"><b>Páratartalom:</b> <span id="humidity">--</span></div>
    <div class="data"><b>Hőmérséklet (C):</b> <span id="tempC">--</span></div>
    <div class="data"><b>Hőmérséklet (F):</b> <span id="tempF">--</span></div>
    <div class="data"><b>Hőérzet (C):</b> <span id="heatC">--</span></div>
    <div class="data"><b>Hőérzet (F):</b> <span id="heatF">--</span></div>
  </body>
  </html>
  )rawliteral";

  server->send(200, "text/html", html);
}

// JSON endpoint
void handleData() {
  String json = "{";
  json += "\"status\":\"" + dht_getStatus() + "\",";
  json += "\"humidity\":" + String(dht_getHumidity(), 1) + ",";
  json += "\"tempC\":" + String(dht_getTemperature(), 1) + ",";
  json += "\"tempF\":" + String(dht_getTemperatureF(), 1) + ",";
  json += "\"heatC\":" + String(dht_getHeatIndexC(), 1) + ",";
  json += "\"heatF\":" + String(dht_getHeatIndexF(), 1);
  json += "}";
  server->send(200, "application/json", json);
}

// inicializálás
void webserver_init(uint16_t port) {
  server = new WebServer(port);

  Serial.println("WiFi-hez csatlakozás...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Csatlakozva. IP cím: ");
  Serial.println(WiFi.localIP());

  server->on("/", handleRoot);
  server->on("/data", handleData);

  server->begin();
  Serial.printf("Webszerver elindult a %d porton\n", port);
}

// fő ciklusból hívható
void webserver_handle() {
  if (server) {
    server->handleClient();
  }
}
