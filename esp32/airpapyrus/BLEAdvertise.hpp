#ifndef BLE_ADVERTISE_HPP
#define BLE_ADVERTISE_HPP

#include <string>
#include <BLEServer.h>
#include "BLEAdvertisePayload.hpp"

class BLEAdvertise {
private:
  BLEServer *server;

  uint8_t sequenceNumber;

  template<typename T>
  static std::string ToBinaryString(const T& data);

  BLEAdvertisementData generateAdvertisementData(const BLEAdvertisePayload payload);

public:
  explicit BLEAdvertise();

  void initialize();

  void setPayload(const BLEAdvertisePayload payload);

  void start();
  void stop();
};

#endif
