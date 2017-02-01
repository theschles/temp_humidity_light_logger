#include "serialHelper.h"
#include "wifiHelper.h"
#include "hdc1000Helper.h"
#include "Arduino.h"

float temp,rh;

void setup() {
  setupSerial();
  setupWiFi();
}

void loop() {
  temp = getTemp();
  rh = getRh();
  uploadDataToCloud();
}
