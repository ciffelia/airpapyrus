#include "BME280Data.hpp"

BME280Data::BME280Data(const float _temperature, const float _humidity, const float _pressure)
  : temperature(_temperature), humidity(_humidity), pressure(_pressure)
{
}
