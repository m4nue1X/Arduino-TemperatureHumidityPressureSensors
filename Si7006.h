
/**********************************************************
 * Si7006.h                                          *
 *                                                        *
 * Author: Manuel Schoch <info@manuel-schoch.net>         *
 *                                                        *
 **********************************************************/

#ifndef SI7006_H
#define SI7006_H

#include <Arduino.h>

class Si7006 {
public:
  // Device address
  static constexpr uint8_t kSi7006Addr = 0x40;
  // Resister addresses
  // NOTE: reading from / writing to registers also triggers commands
  static constexpr uint8_t kSi7006RegHumidityMeasurementHoldMaster = 0xE5;
  static constexpr uint8_t kSi7006RegHumidityMeasurementAsync = 0xF5;
  static constexpr uint8_t kSi7006RegTemperatureMeasurmentHoldMaster = 0xE3;
  static constexpr uint8_t kSi7006RegTemperatureMeasurmentAsync = 0xF3;
  static constexpr uint8_t kSi7006RegTemperatureFromHumidityMeasurment = 0xE0;
  static constexpr uint8_t kSi7006RegReset = 0xFE;
  static constexpr uint8_t kSi7006RegWriteUserRegister1 = 0xE6;
  static constexpr uint8_t kSi7006RegReadUserRegister1 = 0xE7;
  static constexpr uint8_t kSi7006RegWriteHeaterCtrlRegister = 0x51;
  static constexpr uint8_t kSi7006RegReadHeaterCtrlRegister = 0x11;
  static constexpr uint8_t kSi7006RegReadIDHigh4 = 0x0F;
  static constexpr uint8_t kSi7006RegReadIDLow4 = 0xc9;
  static constexpr uint8_t kSi7006RegReadFirmwareRev = 0xB8;
  
  static constexpr uint8_t kSi7006UserRegister1Default = 0x3A;
  static constexpr uint8_t kSi7006HeaterCtrlRegisterDefault = 0x0;
  
  enum class Resolution : uint8_t {
    kHumidity12Temp14Bit = 0x0,
    kHumidity8Temp12Bit = 0x0 << 7 | 0x1,
    klHumidity10Temp13Bit = 0x1 << 7 | 0x0,
    kHumidity11Temp11Bit = 0x1 << 7 | 0x1
  };
  
  enum class HeaterEnable : uint8_t {
    kDisable = 0x0,
    kEnable = 0x1 << 2
  };
  
  enum class HeaterPower : uint8_t {
    Power3Dot09MA = 0x0,
    Power9Dot18MA = 0x1,
    Power15Dot24MA = 0x2,
    Power21Dot32MA = 0x3, //  +6.075
    Power27Dot39MA = 0x4,
    Power33Dot47MA = 0x5,
    Power39Dot54MA = 0x6,
    Power45Dot62MA = 0x7,
    Power51Dot69MA = 0x8,
    Power57Dot77MA = 0x9,
    Power63Dot84MA = 0xA,
    Power69Dot92MA = 0xB,
    Power75Dot99MA = 0xC,
    Power82Dot7MA = 0xD,
    Power88Dot14MA = 0xE,
    Power94Dot20MA = 0xF
  };
  
  /**
   * Configure the chip. The chip has a built in heater for more precise humidity measurements
   * especially in humid conditions. However, using the heater affects the accuracy of the temperature
   * measurments.
   */
  int configure(Resolution res, bool enable_heater=false, HeaterPower heater_power=HeaterPower::Power3Dot09MA);
  
  /**
   * Triggers a humidity and temperature measurment and returns the measurments. Temperature 
   * is always reported in degree celsius, relative humidity in percent. The measurement itself
   * takes 18-19ms. The mechod will block for that time.
   */
  int measureTemperatureAndHumidity(float& temperature, float& humidity);
  
};
#endif // SI7006_H
