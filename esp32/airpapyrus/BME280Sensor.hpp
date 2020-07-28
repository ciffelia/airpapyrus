#ifndef BME280_SENSOR_HPP
#define BME280_SENSOR_HPP

#include <SparkFunBME280.h>
#include "BME280Data.hpp"

class BME280Sensor {
private:
  BME280 bme280;

public:
  explicit BME280Sensor();

  bool initialize();

  BME280Data read();
};

#endif
