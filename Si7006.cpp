
#include "Si7006.h"
#include <WireUtil.h>

int Si7006::configure(Resolution res, bool enable_heater, HeaterPower heater_power) {
  if(WireUtil::writeRegister(kSi7006Addr, kSi7006RegWriteUserRegister1, kSi7006UserRegister1Default | uint8_t(res) | uint8_t(enable_heater ? HeaterEnable::kEnable : HeaterEnable::kDisable)) != 0 ||
     WireUtil::writeRegister(kSi7006Addr, kSi7006RegWriteHeaterCtrlRegister, kSi7006HeaterCtrlRegisterDefault | uint8_t(heater_power)) != 0) {
    return -1;
  }
  
  return 0;
}

int Si7006::measureTemperatureAndHumidity(float& temperature, float& humidity) {
  // NOTE: The humidy meaurement takes usually 18-19ms to finish. We allow 20ms.
  uint32_t humidity_raw, temperature_raw;
  if (WireUtil::readRegister(0x40, 0xF5, 2, humidity_raw, false, 20e3) == 0 && 
      WireUtil::readRegister(0x40, 0xE0, 2, temperature_raw, false, 0) == 0) {
    humidity = 125 * humidity_raw / 65536.0 - 6;
    temperature = 175.72 * temperature_raw / 65536.0 - 46.85;
    return 0;
  }
  return -1;
}
