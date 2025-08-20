#ifndef _FUTABA_VFD_H_
#define _FUTABA_VFD_H_

#include <Arduino.h>
#include <SPI.h>

// 0.5 MHz is the max serial clock frequency
// 时钟上升沿采样，空闲高电平，即SPI模式3；LSB First
#define FUTABA_VFD_MAX_CP_FREQ 500000

#define FUTABA_VFD_DEF_DIGIT 8
#define FUTABA_VFD_MAX_DIGIT 16
#define FUTABA_VFD_MAX_BRIGHTNESS 240

// Commonds
// 或上第几位(5 bit)，接着 UTF8 字符编码，即共 2 bytes
#define FUTABA_VFD_CMD_DCRAM_DATA_WRITE 0x20

// 或上地址(3 bit)，接着 5 bytes(5 x 7点阵，即最高位被弃用)，即共 6 bytes
#define FUTABA_VFD_CMD_CGRAM_DATA_WRITE 0x40

// 直接接上显示位数（7 bit），即共 2 bytes
#define FUTABA_VFD_CMD_DIGIT_SET 0xE0

// 直接接上亮度值（1 byte, max is 240），即共 2 bytes
#define FUTABA_VFD_CMD_DIMMING_SET 0xE4

// 直接发送，即共 1 byte
#define FUTABA_VFD_CMD_DISPLAY_ON 0xE8

// 直接发送，即共 1 byte
#define FUTABA_VFD_CMD_DISPLAY_OFF 0xEA

// 或上是否开启，1 为开启待机（1 bit），即共 1 byte
#define FUTABA_VFD_CMD_SET_STANDBY_MODE 0xEC

class FutabaVFD {
public:
  FutabaVFD(int csPin, SPIClass *spi = &SPI);

  void writeCustomPattern(uint8_t addr, const uint8_t pattern[5]);
  void showCustomPattern(uint8_t dig, uint8_t addr);

  void showCharacter(uint8_t dig, const char c);
  void showString(uint8_t dig, const char *str);
  void showString(uint8_t dig, String str);

  void setBrightness(uint8_t brightness);
  void setDigit(uint8_t digit);
  void displayOn();
  void displayOff();
  void setStandbyMode(bool standby);

private:
  int _csPin;
  SPIClass *_spi;

  void init();
  void sendCommand(uint8_t cmd);
  void sendCommandWithData(uint8_t cmd, uint8_t *data, size_t data_len);
};

#endif // _FUTABA_VFD_H_
