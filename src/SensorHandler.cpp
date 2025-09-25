#include "SensorHandler.h"
#include "DHTesp.h"
#include <vector>

#define DHTPIN 22
DHTesp dht;

std::vector<DHTSample> dailyData;
// tároljuk a napi kezdő millis-t
unsigned long dayStartMillis = 0;

void setupSensor() {
  dht.setup(DHTPIN, DHTesp::DHT22);
  dayStartMillis = millis(); // napi kezdés
}

float getTemperature() {
  return dht.getTemperature();
}

float getHumidity() {
  return dht.getHumidity();
}

void readSensor() {
// ha több mint 24 óra telt el, reset
  if (millis() - dayStartMillis > 24UL*60UL*60UL*1000UL) {
    resetDailyData();
    dayStartMillis = millis();
  }

  float t = dht.getTemperature();
  float h = dht.getHumidity();
  if (!isnan(t) && !isnan(h)) {
    unsigned long ts = millis(); // timestamp a napi millis-hez képest
    dailyData.push_back({ts, t, h});
    Serial.printf("T=%.1f °C, H=%.1f %%\n", t, h);
  }
}

std::vector<DHTSample>& getDailyData() {
  return dailyData;
}

void resetDailyData() {
  dailyData.clear();
}