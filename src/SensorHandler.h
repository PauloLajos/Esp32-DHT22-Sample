#ifndef SENSOR_HANDLER_H
#define SENSOR_HANDLER_H

#include <Arduino.h>
#include <vector>

struct DHTSample {
  unsigned long timestamp; // UNIX timestamp millis
  float temperature;
  float humidity;
};

void setupSensor();
void readSensor();             // 3 másodpercenként hívva
std::vector<DHTSample>& getDailyData();  // a webserver lekérheti az adatokat
float getTemperature();
float getHumidity();
void resetDailyData();

#endif
