#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_HDC1000.h>

Adafruit_HDC1000 hdc;

#ifndef HDC1000_DEBUG
#define HDC1000_DEBUG 1
#endif

bool isHDC1000Debug() {
  return (HDC1000_DEBUG == 1);
}

void setupHDC1000() {
  hdc = Adafruit_HDC1000();
  if (!hdc.begin()) {
    if (isHDC1000Debug()) {
      Serial.println("Couldn't find sensor!");
    }
    while (10);
  }
}

float getTemp() {
  float temp = hdc.readTemperature()*1.8+32.0;
  if (isHDC1000Debug()) {
    Serial.print("\nTemp: ");
    Serial.println(temp);
  }
  return temp;
}

float getRh() {
  float rh = hdc.readHumidity();
  if (isHDC1000Debug()) {
    Serial.print("\nHum: ");
    Serial.println(rh);
  }
  return rh;
}
