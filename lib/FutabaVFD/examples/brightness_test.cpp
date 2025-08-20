// Brightness test for FutabaVFD library
#include <Arduino.h>
#include <SPI.h>
#include "FutabaVFD.h"

#define VFD_CS_PIN 10
FutabaVFD vfd(VFD_CS_PIN, &SPI);

void setup() {
    vfd.setDigit(8);
    vfd.displayOn();
}

void loop() {
    for (uint8_t b = 0; b <= 7; b++) {
        vfd.setBrightness(b);
        vfd.showString(0, String("BRIGHT ") + String(b));
        delay(800);
    }
}
