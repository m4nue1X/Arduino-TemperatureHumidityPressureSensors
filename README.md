## Si7006

The Silicon Labs 7006 is a temperature and humidity sensor. The chip uses I2C for communication with 
the host.

This library provides an easy to use API for Arduino that supports the basic functionality of the
sensor.

Dependencies: Arduino-WireUtil, Arduino-TimeUtil

Example:
~~~~
#include <Si7006.h>

Si7006 temperature_sensor;

void setup() {
  Wire.begin(4, 5);
  delay(100);
  
  // Temperature sensor setup
  temperature_sensor.configure(Si7006::Resolution::kHumidity12Temp14Bit, false);
}

int last_run = 0;

void loop() {
  int now = millis();
  if(now >= last_run + 1000) {
    last_run = now;
    
    // Read temperature and humidity
    float temperature_tmp, humidity_tmp;
    if(temperature_sensor.measureTemperatureAndHumidity(temperature_tmp, humidity_tmp) == 0) {
      Serial.printf("Humidity: %f%%\n", humidity_tmp);
      Serial.printf("Temperature: %f°C\n", temperature_tmp);
    }
  }
}
~~~~
