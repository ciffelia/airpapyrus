#include <Wire.h>
#include "Constants.hpp"
#include "Logger.hpp"
#include "BME280Sensor.hpp"
#include "CCS811Sensor.hpp"

BME280Sensor bme280;
CCS811Sensor ccs811;

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

  Println("Finished setup().");
}

void loop() {
  Println("Stating loop()...");

  const auto bme280Data = bme280.read();
  Printf(
    "Temperature: %.1f ℃, Humidity: %.1f %%, Pressure: %.1f Pa",
    bme280Data.temperature,
    bme280Data.humidity,
    bme280Data.pressure
  );

  ccs811.setEnvironmentalData(bme280Data);

  const auto ccs811Data = ccs811.read();
  Printf(
    "CO₂: %u ppm, TVOC: %u ppb",
    ccs811Data.co2,
    ccs811Data.tvoc
  );

  Serial.printf(
    "[airpapyrus_report]%f,%f,%f,%u,%u\r\n",
    bme280Data.temperature,
    bme280Data.humidity,
    bme280Data.pressure,
    ccs811Data.co2,
    ccs811Data.tvoc
  );

  Println("Finished loop().");
  delay(30 * 1000);
}
