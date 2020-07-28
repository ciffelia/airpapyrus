#include "CCS811Sensor.hpp"

#include "Constants.hpp"
#include "Logger.hpp"

CCS811Sensor::CCS811Sensor()
  : ccs811(Constants::GPIO::Address::CCS811)
{
}

void CCS811Sensor::reset() {
  pinMode(Constants::GPIO::Pin::CCS811_RESET, OUTPUT);

  digitalWrite(Constants::GPIO::Pin::CCS811_RESET, 0);
  delay(10);
  digitalWrite(Constants::GPIO::Pin::CCS811_RESET, 1);
  delay(10);
}

void CCS811Sensor::wake() {
  pinMode(Constants::GPIO::Pin::CCS811_WAKE, OUTPUT);

  digitalWrite(Constants::GPIO::Pin::CCS811_WAKE, 0);
  
  delay(10);
}

void CCS811Sensor::sleep() {
  pinMode(Constants::GPIO::Pin::CCS811_WAKE, OUTPUT);

  digitalWrite(Constants::GPIO::Pin::CCS811_WAKE, 1);
  
  delay(10);
}

bool CCS811Sensor::waitForDataAvailable(const int timeout) {
  for (int elapsed = 0; elapsed < timeout * 10 && !ccs811.dataAvailable(); elapsed++) {
    delay(100);
  }

  return ccs811.dataAvailable();
}

bool CCS811Sensor::initialize() {
  this->reset();
  this->wake();

  const auto beginStatus = ccs811.beginWithStatus();

  if (beginStatus != CCS811::CCS811_Stat_SUCCESS)
  {
    Printf("ccs811.begin() failed. Error: %s.", ccs811.statusString(beginStatus));
    return false;
  }

  // Mode 1: measurement every second
  const auto setModeStatus = ccs811.setDriveMode(1);

  if (setModeStatus != CCS811::CCS811_Stat_SUCCESS)
  {
    Printf("ccs811.setDriveMode() failed. Error: %s.", ccs811.statusString(setModeStatus));
    return false;
  }

  // 600秒待ってもデータを読み出せなければ諦める
  if (!this->waitForDataAvailable(600)) {
    Println("waitForDataAvailable() timed out. (600s)");
    return false;
  }

  return true;
}

bool CCS811Sensor::setEnvironmentalData(const BME280Data bme280Data) {
  const auto status = ccs811.setEnvironmentalData(bme280Data.humidity, bme280Data.temperature);
  
  if (status != CCS811::CCS811_Stat_SUCCESS)
  {
    Printf("ccs811.setEnvironmentalData() failed. Error: %s.", ccs811.statusString(status));
    return false;
  }

  return true;
}

CCS811Data CCS811Sensor::read() {
  // 15秒待ってもデータを読み出せなければ諦める
  if (!this->waitForDataAvailable(15)) {
    Println("waitForDataAvailable() timed out. (15s)");
    Println("Resetting CCS811...");
    this->initialize();
    return this->read();
  }

  ccs811.readAlgorithmResults();
  return CCS811Data(
    ccs811.getCO2(),
    ccs811.getTVOC()
  );
}
