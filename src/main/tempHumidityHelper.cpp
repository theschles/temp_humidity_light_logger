#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_HDC1000.h>

Adafruit_HDC1000 hdc;

#ifndef TEMP_RH_DEBUG
#define TEMP_RH_DEBUG 0
#endif

bool isTempHumidityDebug() {
  return (TEMP_RH_DEBUG == 1);
}

void setupTempHumidity() {
  hdc = Adafruit_HDC1000();
  if (!hdc.begin()) {
    if (isTempHumidityDebug()) {
      Serial.println("Couldn't find sensor!");
    }
    while (10);
  }
}

float getTemp() {
  float temp = hdc.readTemperature()*1.8+32.0;
  if (isTempHumidityDebug()) {
    String debugOutput = String("\nTemp: ") + temp;
    Serial.println(debugOutput);
  }
  return temp;
}

float getRh() {
  float rh = hdc.readHumidity();
  if (isTempHumidityDebug()) {
    String debugOutput = String("\nRh: ") + rh;
    Serial.println(debugOutput);
  }
  return rh;
}
