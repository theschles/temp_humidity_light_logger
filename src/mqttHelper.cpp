#include "mqttProperties.cpp"
#include <ESP8266WiFi.h>
#include "Arduino.h"

#ifndef MQTT_DEBUG
#define MQTT_DEBUG 1
#endif

bool isMQTTDebug() {
 return (MQTT_DEBUG == 1);
}

void setupMQTT() {
}

void publishMQTT() {
  if (isMQTTDebug()) {
    String debugOutput = String("");
    Serial.println(debugOutput);
  }
}
