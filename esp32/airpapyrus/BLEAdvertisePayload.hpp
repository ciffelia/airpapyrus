#ifndef BLE_ADVERTISE_PAYLOAD_HPP
#define BLE_ADVERTISE_PAYLOAD_HPP

#include "BME280Data.hpp"
#include "CCS811Data.hpp"

struct BLEAdvertisePayload {
  explicit BLEAdvertisePayload(const BME280Data bme280Data, const CCS811Data ccs811Data);

  float temperature;
  float humidity;
  float pressure;

  uint16_t co2;
  uint16_t tvoc;
};

#endif
