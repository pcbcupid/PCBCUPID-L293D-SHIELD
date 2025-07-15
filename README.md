# PCBCUPID MCP79412 RTC Library

An enhanced Arduino library for the Microchip MCP7941x Real-Time Clock/Calendar chips with improved ESP32 compatibility (supports all [GLYPH](https://shop.pcbcupid.com/product-category/development-boards/)development boards) and comprehensive examples.

## Overview

PCBCUPID MCP79412 RTC is a feature-rich Arduino library that supports the Microchip MCP7941x Real-Time Clock/Calendar family. Built upon the foundation of the original MCP79412RTC library, we've made significant enhancements to improve compatibility and expand functionality.

This library is designed to work seamlessly with PJRC's Arduino Time library and provides extensive support for all MCP79412 features including dual alarms, battery-backed SRAM, EEPROM storage, power failure detection, and calibration capabilities.

## Key Features & Enhancements

### **Enhanced Compatibility**
- **ESP32 Support**: Modified Wire library implementation to use TwoWire interface for full ESP32 board compatibility
- **Flexible I2C Configuration**: Multiple begin() methods supporting custom SDA/SCL pins, clock frequencies, and TwoWire instances
- **Cross-Platform**: Maintains compatibility with traditional Arduino boards while extending support to modern ESP32 platforms
- **Multi-I2C Support**: Support for multiple I2C buses with custom TwoWire instances

### **Comprehensive Examples**
We've significantly expanded the example collection to demonstrate every feature of the MCP79412 RTC:

- **Basic Time Operations**: Setting and reading time with various methods
- **Dual Alarm System**: Complete examples for both Alarm-0 and Alarm-1 configurations
- **Power Management**: Battery backup, power failure detection, and logging
- **Memory Operations**: SRAM and EEPROM read/write demonstrations
- **Calibration**: Fine-tuning RTC accuracy with calibration examples
- **Advanced Features**: Square wave generation, unique ID reading, and multi-function pin control
- **Real-World Applications**: Practical implementations including data loggers and scheduling systems

## Hardware Support

**Supported RTC Chips:**
- MCP79411 (EUI-48 MAC address)
- MCP79412 (EUI-64 MAC address)

**Compatible Platforms:**
- [Glyph Development Board](https://shop.pcbcupid.com/product-category/development-boards/)
- Arduino Uno, Nano, Pro Mini
- Arduino Mega, Leonardo
- ESP32 (all variants)
- Other Arduino-compatible boards with I2C support

## Core Features & Functions

### **Time Management**
- `get()` - Get current time as time_t
- `set(time_t t)` - Set RTC time from time_t
- `read(tmElements_t &tm)` - Read time into tmElements_t structure
- `write(tmElements_t &tm)` - Write time from tmElements_t structure
- `isRunning()` - Check if RTC oscillator is running

### **Dual Alarm System**
- `setAlarm(alarmNumber, alarmTime)` - Set alarm time (ALARM_0 or ALARM_1)
- `enableAlarm(alarmNumber, alarmType)` - Enable/configure alarm matching criteria
- `alarm(alarmNumber)` - Check and clear alarm flag
- `alarmPolarity(polarity)` - Set alarm output polarity

**Alarm Match Types:**
- `ALM_MATCH_SECONDS` - Match seconds
- `ALM_MATCH_MINUTES` - Match minutes  
- `ALM_MATCH_HOURS` - Match hours
- `ALM_MATCH_DAY` - Match day of week (triggers at midnight)
- `ALM_MATCH_DATE` - Match date (triggers at midnight)
- `ALM_MATCH_DATETIME` - Match complete date and time
- `ALM_DISABLE` - Disable alarm

### **Memory Operations**

**64-Byte Battery-Backed SRAM:**
- `sramWrite(addr, value)` - Write single byte
- `sramWrite(addr, values[], nBytes)` - Write multiple bytes
- `sramRead(addr)` - Read single byte
- `sramRead(addr, values[], nBytes)` - Read multiple bytes

**128-Byte EEPROM Storage:**
- `eepromWrite(addr, value)` - Write single byte
- `eepromWrite(addr, values[], nBytes)` - Write page (up to 8 bytes)
- `eepromRead(addr)` - Read single byte
- `eepromRead(addr, values[], nBytes)` - Read multiple bytes

### **Power Management**
- `vbaten(enable)` - Enable/disable battery backup
- `powerFail(powerDown, powerUp)` - Check for power failures and get timestamps
- Power failure detection with automatic timestamping
- Battery backup support for continuous operation

### **Advanced Features**
- `calibRead()` / `calibWrite(value)` - Clock calibration (±127 PPM adjustment)
- `squareWave(freq)` - Generate square wave output (1Hz, 4096Hz, 8192Hz, 32768Hz, or disable)
- `out(level)` - Set MFP output level when not used for alarms/square wave
- `idRead(uniqueID[])` - Read 64-bit unique ID
- `getEUI64(uniqueID[])` - Get EUI-64 format MAC address

**Square Wave Frequencies:**
- `SQWAVE_1_HZ` - 1 Hz output
- `SQWAVE_4096_HZ` - 4.096 kHz output  
- `SQWAVE_8192_HZ` - 8.192 kHz output
- `SQWAVE_32768_HZ` - 32.768 kHz output
- `SQWAVE_NONE` - Disable square wave


## Documentation & Resources

- **Microchip MCP79412 Datasheet**: [Product Page](https://www.microchip.com/wwwproducts/en/MCP79412)
- **Arduino Time Library**: [PJRC Time Library Documentation](https://github.com/PaulStoffregen/Time)
- **Examples**: Comprehensive example sketches included with the library
- **Community Support**: Active community support through GitHub issues & dedicated [forum](https://forum.pcbcupid.com/)

## Credits & Attribution

This library is inspired by and builds upon the excellent work of **Jack Christensen's MCP79412RTC library**. We are deeply grateful for his foundational work that made this enhanced version possible.

**Original Work:**
- **Author**: Jack Christensen
- **Original Repository**: [JChristensen/MCP79412RTC](https://github.com/JChristensen/MCP79412RTC)
- **License**: GNU GPL v3.0

We thank Jack Christensen for his contribution to the open-source Arduino community and for creating such a solid foundation for MCP79412 development. This enhanced version aims to extend his excellent work to modern platforms while preserving the quality and reliability of the original implementation.

## Contributing

We welcome contributions! Please see our [Contributing Guidelines](CONTRIBUTING.md) for details on how to submit bug reports, feature requests, and pull requests.

## License

This library is released under the same license terms as the original MCP79412RTC library (GNU GPL v3.0). Please see the LICENSE file for details.

---

**Made with ❤️ by the PCBCUPID**