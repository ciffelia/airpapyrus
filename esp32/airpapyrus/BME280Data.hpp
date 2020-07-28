#ifndef BME280_DATA_HPP
#define BME280_DATA_HPP

struct BME280Data {
  explicit BME280Data(const float temperature, const float humidity, const float pressure);

  float temperature;
  float humidity;
  float pressure;
};

#endif
