#include <Arduino.h>
#include "SensorHandler.h"
#include "WebServerHandler.h"

void setup() {
  Serial.begin(9600);
  setupSensor();
  setupWebServer();
}

void loop() {
  handleWebServer();
}
