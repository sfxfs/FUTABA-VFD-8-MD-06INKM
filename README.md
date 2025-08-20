
# FUTABA-VFD-8-MD-06INKM Driver

English | [简体中文](README_CN.md)

*A modern Arduino/PlatformIO driver for the Futaba 8-MD-06INKM VFD display (SPI interface)*

## Features

- Easy-to-use C++ class: `FutabaVFD`
- Supports up to 16 digits (configurable)
- Adjustable brightness (0~240)
- Custom character (5x7 dot matrix) support
- Standby (power-saving) mode
- Full SPI hardware support (mode 3, LSB first)
- Example and test code included

## Getting Started

### 1. Hardware

- Connect the VFD display to your MCU's SPI bus (see datasheet for pinout)
- Set the CS (chip select) pin in your code (default: 10)

### 2. Usage Example

```cpp
#include <Arduino.h>
#include <SPI.h>
#include "FutabaVFD.h"

#define VFD_CS_PIN 10
FutabaVFD vfd(VFD_CS_PIN, &SPI);

void setup() {
	vfd.setDigit(8);
	vfd.setBrightness(120);
	vfd.displayOn();
	vfd.showString(0, "HELLO123");
}

void loop() {
	// Count up demo
	static int count = 0;
	char buf[9];
	snprintf(buf, sizeof(buf), "%8d", count++);
	vfd.showString(0, buf);
	delay(500);
}
```

More examples can be found in `lib/FutabaVFD/examples/`.

## API Overview

| Method | Description |
| ------ | ----------- |
| `setDigit(uint8_t digit)` | Set number of display digits (1~16) |
| `setBrightness(uint8_t brightness)` | Set brightness (0~240) |
| `showCharacter(uint8_t pos, char c)` | Show a character at position |
| `showString(uint8_t pos, const char* str)` | Show a string from position |
| `writeCustomPattern(uint8_t addr, const uint8_t pattern[5])` | Write a custom 5x7 pattern |
| `showCustomPattern(uint8_t pos, uint8_t addr)` | Show a custom pattern at position |
| `displayOn()` / `displayOff()` | Turn display on/off |
| `setStandbyMode(bool standby)` | Enter/exit standby mode |
