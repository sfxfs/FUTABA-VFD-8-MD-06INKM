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

#include "FutabaVFD.h"

FutabaVFD::FutabaVFD(int csPin, SPIClass &spi) : m_csPin(csPin), m_spi(spi)
{
  pinMode(m_csPin, OUTPUT);
  digitalWrite(m_csPin, HIGH);
  init();
}

void FutabaVFD::init()
{
  m_spi.begin();
  // SPI设置：模式3，LSB First，0.5MHz
  m_spi.beginTransaction(
      SPISettings(max_cp_freq, LSBFIRST, SPI_MODE3));
  setDigit(default_digit);           // 默认8位
  setBrightness(default_brightness); // 默认最大亮度
  displayOn();
}

void FutabaVFD::sendCommand(uint8_t cmd)
{
  digitalWrite(m_csPin, LOW);
  m_spi.transfer(cmd);
  digitalWrite(m_csPin, HIGH);
}

void FutabaVFD::sendCommandWithData(uint8_t cmd, const std::vector<uint8_t> &data)
{
  digitalWrite(m_csPin, LOW);
  m_spi.transfer(cmd);
  for (auto byte : data)
  {
    m_spi.transfer(byte);
  }
  digitalWrite(m_csPin, HIGH);
}

void FutabaVFD::writeCustomPattern(uint8_t addr, const uint8_t pattern[5])
{
  sendCommandWithData(cmd_write_cgram_data | (addr & 0x07),
                      {pattern, pattern + 5});
}

void FutabaVFD::showCustomPattern(uint8_t dig, uint8_t addr)
{
  sendCommandWithData(cmd_write_dcram_data | (dig & 0x1F),
                      {addr});
}

void FutabaVFD::showCharacter(uint8_t dig, const char c)
{
  // dig: 0~7
  sendCommandWithData(cmd_write_dcram_data | (dig & 0x1F),
                      {static_cast<uint8_t>(c)});
}

void FutabaVFD::showString(uint8_t dig, String str)
{
  sendCommandWithData(cmd_write_dcram_data | (dig & 0x1F),
                      {str.begin(), str.end()});
}

void FutabaVFD::showString(uint8_t dig, const char *str)
{
  sendCommandWithData(cmd_write_dcram_data | (dig & 0x1F),
                      {str, str + strlen(str)});
}

void FutabaVFD::setBrightness(uint8_t brightness)
{
  brightness = constrain(brightness, 0, max_brightness);
  sendCommandWithData(cmd_set_dimming, {brightness});
}

void FutabaVFD::setDigit(uint8_t digit)
{
  digit = constrain(digit, 1, max_digit);
  digit--;
  sendCommandWithData(cmd_set_digit, {digit});
}

void FutabaVFD::displayOn() { sendCommand(cmd_display_on); }

void FutabaVFD::displayOff() { sendCommand(cmd_display_off); }

void FutabaVFD::setStandbyMode(bool standby)
{
  uint8_t cmd = cmd_set_standby_mode | (standby ? 0x01 : 0x00);
  sendCommand(cmd);
}
