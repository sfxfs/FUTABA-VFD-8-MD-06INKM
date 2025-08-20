
# FUTABA 8-MD-06INKM VFD 显示屏驱动

[English](README.md) | 简体中文

*适用于 Futaba 8-MD-06INKM VFD 显示屏的现代 Arduino/PlatformIO 驱动库（SPI 接口）*

## 特性

- 现代 C++ 类接口：`FutabaVFD`
- 支持 1~16 位数码管显示
- 亮度可调（0~240）
- 支持自定义 5x7 点阵字符
- 省电待机模式
- 完全支持硬件 SPI（模式3，LSB优先）
- 提供丰富示例与自动化测试

## 快速上手

### 1. 硬件连接

- 按照规格书将 VFD 显示屏连接到 MCU 的 SPI 总线
- 在代码中设置片选（CS）引脚（默认 10）

### 2. 代码示例

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
	// 计数动画演示
	static int count = 0;
	char buf[9];
	snprintf(buf, sizeof(buf), "%8d", count++);
	vfd.showString(0, buf);
	delay(500);
}
```

更多用法见 `lib/FutabaVFD/examples/`。

## 主要接口

| 方法 | 说明 |
| ---- | ---- |
| `setDigit(uint8_t digit)` | 设置显示位数（1~16） |
| `setBrightness(uint8_t brightness)` | 设置亮度（0~240） |
| `showCharacter(uint8_t pos, char c)` | 指定位置显示单字符 |
| `showString(uint8_t pos, const char* str)` | 指定位置显示字符串 |
| `writeCustomPattern(uint8_t addr, const uint8_t pattern[5])` | 写入自定义 5x7 点阵字符 |
| `showCustomPattern(uint8_t pos, uint8_t addr)` | 指定位置显示自定义字符 |
| `displayOn()` / `displayOff()` | 开关显示 |
| `setStandbyMode(bool standby)` | 进入/退出待机模式 |

