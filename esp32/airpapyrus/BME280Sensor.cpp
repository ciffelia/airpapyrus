#include "BME280Sensor.hpp"

#include "Constants.hpp"
#include "Logger.hpp"

BME280Sensor::BME280Sensor()
  : bme280()
{
}

bool BME280Sensor::initialize() {
  bme280.setI2CAddress(Constants::GPIO::Address::BME280);
  
  return bme280.beginI2C();
}

BME280Data BME280Sensor::read() {
  return BME280Data(
    bme280.readTempC(),
    bme280.readFloatHumidity(),
    bme280.readFloatPressure()
  );
}
