#include "serialHelper.h"
#include "wifiHelper.h"
#include "tempHumidityHelper.h"
#include "Arduino.h"

float temp,rh;

void setup() {
  setupSerial();
  setupWiFi();
  setupTempHumidity();
}

void loop() {
  temp = getTemp();
  rh = getRh();
  uploadDataToCloud(temp,rh);
}
