#include "Arduino.h"

#ifndef SERIAL_BPS
#define  SERIAL_BPS 115200
#endif

#ifndef SERIAL_DELAY
#define SERIAL_DELAY 10
#endif

void setupSerial() {
  Serial.begin(SERIAL_BPS);
  delay(SERIAL_DELAY);
}
