#include <Arduino.h>
#include "DHTSensor.h"

#define DHTPIN 22

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)\tHeatIndex (C)\t(F)");

  dht_init(DHTPIN, DHTesp::DHT22);
}

void loop() {
  delay(2000); // mérési ciklus

  Serial.print(dht_getStatus());
  Serial.print("\t");
  Serial.print(dht_getHumidity(), 1);
  Serial.print("\t\t");
  Serial.print(dht_getTemperature(), 1);
  Serial.print("\t\t");
  Serial.print(dht_getTemperatureF(), 1);
  Serial.print("\t\t");
  Serial.print(dht_getHeatIndexC(), 1);
  Serial.print("\t\t");
  Serial.println(dht_getHeatIndexF(), 1);
}
