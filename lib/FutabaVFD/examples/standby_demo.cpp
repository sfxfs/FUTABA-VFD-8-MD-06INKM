// Standby mode demo for FutabaVFD library
#include <Arduino.h>
#include <SPI.h>
#include "FutabaVFD.h"

#define VFD_CS_PIN 10
FutabaVFD vfd(VFD_CS_PIN, &SPI);

void setup() {
    vfd.setDigit(8);
    vfd.setBrightness(7);
    vfd.displayOn();
    vfd.showString(0, "STANDBY");
    delay(2000);
    vfd.setStandbyMode(true); // Enter standby
    delay(2000);
    vfd.setStandbyMode(false); // Exit standby
    vfd.showString(0, "WAKE UP");
}

void loop() {
    // Nothing
}
