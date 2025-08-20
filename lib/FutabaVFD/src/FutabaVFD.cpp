#include "FutabaVFD.h"

FutabaVFD::FutabaVFD(int csPin, SPIClass *spi) : _csPin(csPin), _spi(spi) {
  pinMode(_csPin, OUTPUT);
  digitalWrite(_csPin, HIGH);
  init();
}

void FutabaVFD::init() {
  _spi->begin();
  // SPI设置：模式3，LSB First，0.5MHz
  _spi->beginTransaction(
      SPISettings(FUTABA_VFD_MAX_CP_FREQ, LSBFIRST, SPI_MODE3));
  setDigit(FUTABA_VFD_DEF_DIGIT);           // 默认8位
  setBrightness(FUTABA_VFD_MAX_BRIGHTNESS); // 默认最大亮度
  displayOn();
}

void FutabaVFD::sendCommand(uint8_t cmd) {
  digitalWrite(_csPin, LOW);
  _spi->transfer(cmd);
  digitalWrite(_csPin, HIGH);
}

void FutabaVFD::sendCommandWithData(uint8_t cmd, uint8_t *data,
                                    size_t data_len) {
  digitalWrite(_csPin, LOW);
  _spi->transfer(cmd);
  _spi->transfer(data, data_len);
  digitalWrite(_csPin, HIGH);
}

void FutabaVFD::writeCustomPattern(uint8_t addr, const uint8_t pattern[5]) {
  sendCommandWithData(FUTABA_VFD_CMD_CGRAM_DATA_WRITE | (addr & 0x07),
                      (uint8_t *)pattern, 5);
}

void FutabaVFD::showCustomPattern(uint8_t dig, uint8_t addr) {
  sendCommandWithData(FUTABA_VFD_CMD_DCRAM_DATA_WRITE | (dig & 0x1F),
                      (uint8_t *)&addr, 1);
}

void FutabaVFD::showCharacter(uint8_t dig, const char c) {
  // dig: 0~7
  sendCommandWithData(FUTABA_VFD_CMD_DCRAM_DATA_WRITE | (dig & 0x1F),
                      (uint8_t *)&c, 1);
}

void FutabaVFD::showString(uint8_t dig, String str) {
  sendCommandWithData(FUTABA_VFD_CMD_DCRAM_DATA_WRITE | (dig & 0x1F),
                      (uint8_t *)str.c_str(), str.length());
}

void FutabaVFD::showString(uint8_t dig, const char *str) {
  sendCommandWithData(FUTABA_VFD_CMD_DCRAM_DATA_WRITE | (dig & 0x1F),
                      (uint8_t *)str, strlen(str));
}

void FutabaVFD::setBrightness(uint8_t brightness) {
  if (brightness > FUTABA_VFD_MAX_BRIGHTNESS)
    brightness = FUTABA_VFD_MAX_BRIGHTNESS;
  sendCommandWithData(FUTABA_VFD_CMD_DIMMING_SET, &brightness, 1);
}

void FutabaVFD::setDigit(uint8_t digit) {
  digit = constrain(digit, 1, FUTABA_VFD_MAX_DIGIT);
  digit--;
  sendCommandWithData(FUTABA_VFD_CMD_DIGIT_SET, &digit, 1);
}

void FutabaVFD::displayOn() { sendCommand(FUTABA_VFD_CMD_DISPLAY_ON); }

void FutabaVFD::displayOff() { sendCommand(FUTABA_VFD_CMD_DISPLAY_OFF); }

void FutabaVFD::setStandbyMode(bool standby) {
  uint8_t cmd = FUTABA_VFD_CMD_SET_STANDBY_MODE | (standby ? 0x01 : 0x00);
  sendCommand(cmd);
}
