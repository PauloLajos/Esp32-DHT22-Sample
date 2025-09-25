#include <Arduino.h>
#include "DHTSensor.h"
#include "WebServerHandler.h"

#define DHTPIN 22
#define SERVER_PORT 8081

void setup() {
  Serial.begin(9600);
  dht_init(DHTPIN, DHTesp::DHT22);
  webserver_init(SERVER_PORT);
}

void loop() {
  webserver_handle();
}
