#include <Wire.h>
#include <BLEDevice.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "BME280Sensor.hpp"
#include "CCS811Sensor.hpp"
#include "BLEAdvertise.hpp"

BME280Sensor bme280;
CCS811Sensor ccs811;
BLEAdvertise bleAdvertise;

void setup() {
  Serial.begin(Constants::Serial::SPEED);
  Println("Stating setup()...");

  Wire.begin(
    Constants::GPIO::Pin::I2C_SDA,
    Constants::GPIO::Pin::I2C_SCL
  );

  // Initialize BME280
  if (!bme280.initialize())
  {
    Println("Fatal error in bme280.initialize().");
    esp_deep_sleep_start();
  }

  // Initialize CCS811
  if (!ccs811.initialize()) {
    Println("Fatal error in ccs811.initialize().");
    esp_deep_sleep_start();
  }

  // Initialize BLE module and advertise
  bleAdvertise.initialize();
  bleAdvertise.start();

  Println("Finished setup().");
}

void loop() {
  Println("Stating loop()...");

  const auto bme280Data = bme280.read();
  Printf(
    "Temperature: %f ℃, Humidity: %f %%, Pressure: %f Pa",
    bme280Data.temperature,
    bme280Data.humidity,
    bme280Data.pressure
  );

  ccs811.setEnvironmentalData(bme280Data);

  const auto ccs811Data = ccs811.read();
  Printf(
    "CO2: %u, TVOC: %u",
    ccs811Data.co2,
    ccs811Data.tvoc
  );

  bleAdvertise.setPayload(
    BLEAdvertisePayload(bme280Data, ccs811Data)
  );

  Println("Finished loop().");
  delay(15000);
}
