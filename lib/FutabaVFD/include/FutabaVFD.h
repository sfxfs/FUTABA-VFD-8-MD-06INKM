/*
  MIT License

  Copyright (c) 2022 Xiao

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#pragma once

#include <Arduino.h>
#include <SPI.h>
#include <vector>

/**
 * @brief Class for controlling FUTABA 8-MD-06INKM VFD display via SPI
 */
class FutabaVFD
{
public:
  /**
   * @brief Constructor
   * @param csPin Chip select pin
   * @param spi Pointer to SPIClass, default is &SPI
   */
  FutabaVFD(int csPin, SPIClass &spi = SPI);

  /**
   * @brief Write a custom 5x7 dot pattern to CGRAM
   * @param addr CGRAM address (0-7)
   * @param pattern 5-byte pattern array
   */
  void writeCustomPattern(uint8_t addr, const uint8_t pattern[5]);

  /**
   * @brief Display a custom pattern at a digit position
   * @param dig Digit position (0~15)
   * @param addr CGRAM address (0-7)
   */
  void showCustomPattern(uint8_t dig, uint8_t addr);

  /**
   * @brief Display a single character at a digit position
   * @param dig Digit position (0~15)
   * @param c Character to display
   */
  void showCharacter(uint8_t dig, const char c);

  /**
   * @brief Display a string at a digit position
   * @param dig Start digit position (0~15)
   * @param str String to display (C-string)
   */
  void showString(uint8_t dig, const char *str);

  /**
   * @brief Display a string at a digit position
   * @param dig Start digit position (0~15)
   * @param str String to display (Arduino String)
   */
  void showString(uint8_t dig, String str);

  /**
   * @brief Set display brightness
   * @param brightness Brightness value (0~240)
   */
  void setBrightness(uint8_t brightness);

  /**
   * @brief Set number of display digits
   * @param digit Number of digits (1~16)
   */
  void setDigit(uint8_t digit);

  /**
   * @brief Turn on the display
   */
  void displayOn();

  /**
   * @brief Turn off the display
   */
  void displayOff();

  /**
   * @brief Set standby mode
   * @param standby true: standby, false: normal mode
   */
  void setStandbyMode(bool standby);

private:
  static constexpr uint32_t max_cp_freq{500000}; // 0.5 MHz is the max serial clock frequency
                                                 // Sampled on clock rising edge, idle high, SPI mode 3; LSB First

  static constexpr uint32_t default_digit{8};        // Default digit count
  static constexpr uint32_t max_digit{16};           // Maximum digit count
  static constexpr uint32_t default_brightness{120}; // Default brightness value
  static constexpr uint32_t max_brightness{240};     // Maximum brightness value

  // OR with enable bit, 1 to enable standby (1 bit), total 1 byte
  static constexpr uint8_t cmd_set_standby_mode{0xEC};

  // Send directly, total 1 byte
  static constexpr uint8_t cmd_display_off{0xEA};

  // Send directly, total 1 byte
  static constexpr uint8_t cmd_display_on{0xE8};

  // Directly followed by brightness value (1 byte, max 240), total 2 bytes
  static constexpr uint8_t cmd_set_dimming{0xE4};

  // Directly followed by digit count (7 bits), total 2 bytes
  static constexpr uint8_t cmd_set_digit{0xE0};

  // OR with address (3 bits), then 5 bytes (5x7 dot matrix, highest bit unused), total 6 bytes
  static constexpr uint8_t cmd_write_cgram_data{0x40};

  // OR with digit position (5 bits), then UTF8 character code, total 2 bytes
  static constexpr uint8_t cmd_write_dcram_data{0x20};

  int m_csPin{};   ///< Chip select pin
  SPIClass &m_spi; ///< SPI interface pointer

  void init();
  void sendCommand(uint8_t cmd);
  void sendCommandWithData(uint8_t cmd, const std::vector<uint8_t> &data);
};
