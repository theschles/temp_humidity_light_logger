#include "wifiProperties.cpp"
#include <ESP8266WiFi.h>
#include "Arduino.h"

#ifndef WIFI_DEBUG
#define WIFI_DEBUG 1
#endif

WiFiClient client;

bool isWifiDebug() {
 return (WIFI_DEBUG == 1);
}

void printInitialWifiConnectionDescription() {
  if (isWifiDebug()) {
    String debugOutput = String("\n\nConnecting to ") + WIFI_SSID;
    Serial.println(debugOutput);
  }
}

void connectToWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (isWifiDebug()) {
      String debugOutput = String("Still trying to connect to ") + WIFI_SSID;
      Serial.println(debugOutput);
    }
  }
}

void printWifiConnectionDetails() {
  if (isWifiDebug()) {
    String debugOutput = String("\nWiFi connected to IP address: ") + WiFi.localIP();
    Serial.println(debugOutput);
  }
}

void setupWiFi() {
  printInitialWifiConnectionDescription();
  connectToWifi();
  printWifiConnectionDetails();
}

void pauseBeforeTransferring() {
  delay(MSECS_DELAY_BETWEEN_DATA_TRANSFERS);
}

void describePlannedDataTransmission(float& temp, float& rh, int& vcc) {
  if (isWifiDebug()) {
    String debugOutput = String("Connecting to '")
      + DATA_DESTINATION_HOST
      + "'; sending temp: '"
      + temp
      + "'; rh: '"
      + rh
      + "'; vcc: '"
      + vcc
      + "'";
    Serial.println(debugOutput);
  }
}

bool isCloudConnectionSuccess() {
  return client.connect(DATA_DESTINATION_HOST, DATA_DESTINATION_PORT);
}

String buildConnectionString() {
  return String("GET ")
    + DATA_DESTINATION_PATH
    + " HTTP/1.1\r\n"
    + "Host: "
    + DATA_DESTINATION_HOST
    + "\r\n"
    + "Connection: close\r\n\r\n";
}

void debugConnectionPath() {
  if (isWifiDebug()) {
    String debugOutput = String("Requesting path: ") + DATA_DESTINATION_PATH;
    Serial.println(debugOutput);
  }
}

void sendRequestToCloud() {
  client.print(buildConnectionString());
  delay(10);
}

void printResponseFromCloud() {
  if (isWifiDebug()) {
    while(client.available()){
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    Serial.println("\nclosing connection");
  }
}

bool uploadDataToCloud(float& temp, float& rh, int& vcc) {
  bool success = false;
  pauseBeforeTransferring();
  describePlannedDataTransmission(temp, rh, vcc);
  if (isCloudConnectionSuccess()) {
      debugConnectionPath();
      sendRequestToCloud();
      printResponseFromCloud();
      success = true;
  } else {
    Serial.println("connection failed");
    success = false;
  }
  return success;
}
