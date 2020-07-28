#include "BLEAdvertise.hpp"

#include <algorithm>
#include <BLEDevice.h>
#include "Constants.hpp"

BLEAdvertise::BLEAdvertise()
  : server(nullptr), sequenceNumber(0)
{
}

template<typename T>
std::string BLEAdvertise::ToBinaryString(const T& data) {
  const char *dataChar = (char*)&data;
  const size_t dataSize = sizeof(T);

  return std::string(dataChar, dataSize);
}

BLEAdvertisementData BLEAdvertise::generateAdvertisementData(const BLEAdvertisePayload payload) {
  BLEAdvertisementData advertisementData = BLEAdvertisementData();

  // BR_EDR_NOT_SUPPORTED | LE General Discoverable Mode
  advertisementData.setFlags(0x06);

  const uint8_t payloadLength = sizeof(uint8_t) * 4 + sizeof(BME280Data) + sizeof(CCS811Data);
  
  // Manufacturer specific data
  const uint8_t adType = 0xff;
  
  // Test company ID
  const uint8_t companyIdLow = 0xff;
  const uint8_t companyIdHigh = 0xff;
  
  std::string strServiceData = "";
  strServiceData += (char)payloadLength;
  strServiceData += (char)adType;
  strServiceData += (char)companyIdLow;
  strServiceData += (char)companyIdHigh;
  strServiceData += (char)this->sequenceNumber;
  
  strServiceData += this->ToBinaryString(payload);
  
  advertisementData.addData(strServiceData);
  
  return advertisementData;
}

void BLEAdvertise::initialize() {
  BLEDevice::init(Constants::Bluetooth::SERVER_NAME);

  this->server = BLEDevice::createServer();
}

void BLEAdvertise::setPayload(const BLEAdvertisePayload payload) {
  auto *advertising = this->server->getAdvertising();

  this->sequenceNumber++;
  
  auto advertisementData = this->generateAdvertisementData(payload);
  
  advertising->setAdvertisementData(advertisementData);
}

void BLEAdvertise::start() {
  auto *advertising = this->server->getAdvertising();
  
  advertising->start();
}

void BLEAdvertise::stop() {
  auto *advertising = this->server->getAdvertising();
  
  advertising->stop();
}
