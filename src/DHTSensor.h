#ifndef DHTSENSOR_H
#define DHTSENSOR_H

#include <Arduino.h>
#include "DHTesp.h"

void dht_init(uint8_t pin, DHTesp::DHT_MODEL_t model = DHTesp::DHT22);
float dht_getTemperature();
float dht_getHumidity();
String dht_getStatus();
float dht_getTemperatureF();
float dht_getHeatIndexC();
float dht_getHeatIndexF();

#endif
