#include "serialHelper.h"
#include "wifiHelper.h"
#include "Arduino.h"

void setup() {
  setupSerial();
  setupWiFi();
}

void loop() {
  uploadDataToCloud();
}
