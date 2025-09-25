#include "DHTSensor.h"

static DHTesp dht;        // csak ebben a modulban látszik
static uint8_t dhtPin;    
static DHTesp::DHT_MODEL_t dhtModel;

void dht_init(uint8_t pin, DHTesp::DHT_MODEL_t model) {
  dhtPin = pin;
  dhtModel = model;
  dht.setup(dhtPin, dhtModel);
}

float dht_getTemperature() {
  return dht.getTemperature();
}

float dht_getHumidity() {
  return dht.getHumidity();
}

String dht_getStatus() {
  return dht.getStatusString();
}

float dht_getTemperatureF() {
  return dht.toFahrenheit(dht_getTemperature());
}

float dht_getHeatIndexC() {
  return dht.computeHeatIndex(dht_getTemperature(), dht_getHumidity(), false);
}

float dht_getHeatIndexF() {
  return dht.computeHeatIndex(dht_getTemperatureF(), dht_getHumidity(), true);
}
