#include "serialHelper.h"
#include "vccHelper.h"
#include "wifiHelper.h"
#include "tempHumidityHelper.h"
#include "Arduino.h"

float temp,rh;
int vcc;

void setup() {
  setupSerial();
  setupWiFi();
  setupTempHumidity();
  setupVCC();
}

void loop() {
  vcc = getVCC();
  temp = getTemp();
  rh = getRh();
  uploadDataToCloud(temp,rh,vcc);
}
