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
    Serial.print("\n\nConnecting to ");
    Serial.println(WIFI_SSID);
  }
}

void connectToWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (isWifiDebug()) {
      Serial.print(".");
    }
  }
}

void printWifiConnectionDetails() {
  if (isWifiDebug()) {
    Serial.println("\nWiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
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

void describeToWhereSendingData() {
  if (isWifiDebug()) {
    Serial.print("connecting to ");
    Serial.println(DATA_DESTINATION_HOST);
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
    Serial.print("Requesting path: ");
    Serial.println(DATA_DESTINATION_PATH);
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

bool uploadDataToCloud() {
  bool success = false;
  pauseBeforeTransferring();
  describeToWhereSendingData();
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
