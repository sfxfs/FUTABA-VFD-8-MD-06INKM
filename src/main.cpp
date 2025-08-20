
#include "FutabaVFD.h"
#include <Arduino.h>
#include <SPI.h>

#define VFD_CS_PIN 10
FutabaVFD vfd(VFD_CS_PIN);

void setup() {
  vfd.showString(0, "HELLO123"); // Display string at position 0
  delay(2000);

  vfd.showCharacter(0, 'A'); // Show single character at position 0
  delay(1000);

  vfd.showString(2, "BCD"); // Show string at position 2
  delay(1000);

  vfd.setBrightness(2); // Dim the display
  delay(1000);

  vfd.setBrightness(7); // Restore brightness
  delay(1000);

  vfd.displayOff(); // Turn off display
  delay(1000);

  vfd.displayOn(); // Turn on display again
  delay(1000);

  vfd.setStandbyMode(true); // Enter standby mode
  delay(1000);

  vfd.setStandbyMode(false); // Exit standby mode
  delay(1000);
}

void loop() {
  // Simple animation: count up
  static int count = 0;
  char buf[9];
  snprintf(buf, sizeof(buf), "%8d", count++);
  vfd.showString(0, buf);
  delay(500);
}
