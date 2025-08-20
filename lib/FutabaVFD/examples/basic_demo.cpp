// Basic usage demo for FutabaVFD library
#include <Arduino.h>
#include <SPI.h>
#include "FutabaVFD.h"

#define VFD_CS_PIN 10
FutabaVFD vfd(VFD_CS_PIN, &SPI);

void setup() {
    vfd.setDigit(8);
    vfd.setBrightness(7);
    vfd.displayOn();
    vfd.showString(0, "FUTABA");
}

void loop() {
    static int count = 0;
    char buf[9];
    snprintf(buf, sizeof(buf), "%8d", count++);
    vfd.showString(0, buf);
    delay(500);
}
