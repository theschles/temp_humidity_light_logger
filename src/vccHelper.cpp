#include "Arduino.h"

#ifndef VCC_DEBUG
#define VCC_DEBUG 0
#endif

ADC_MODE(ADC_VCC);

bool isVccDebug() {
 return (VCC_DEBUG == 1);
}

void setupVCC() {
}

int getVCC() {
  int vcc = ESP.getVcc();
  if (isVccDebug()) {
    String debugOutput = String("\nVCC: '") + vcc + "'";
    Serial.println(debugOutput);
  }
  return vcc;
}
