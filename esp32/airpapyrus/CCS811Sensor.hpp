#ifndef CCS811_SENSOR_HPP
#define CCS811_SENSOR_HPP

#include <SparkFunCCS811.h>
#include "CCS811Data.hpp"
#include "BME280Data.hpp"

class CCS811Sensor {
private:
  CCS811 ccs811;

  void reset();
  void wake();
  void sleep();

  bool waitForDataAvailable(const int timeout);

public:
  explicit CCS811Sensor();

  bool initialize();

  bool setEnvironmentalData(const BME280Data bme280Data);

  CCS811Data read();
};

#endif
