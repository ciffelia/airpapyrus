#include "BLEAdvertisePayload.hpp"

BLEAdvertisePayload::BLEAdvertisePayload(const BME280Data bme280Data, const CCS811Data ccs811Data)
  : temperature(bme280Data.temperature)
  , humidity(bme280Data.humidity)
  , pressure(bme280Data.pressure)
  , co2(ccs811Data.co2)
  , tvoc(ccs811Data.tvoc)
{
}
