#include "CCS811Data.hpp"

CCS811Data::CCS811Data(const uint16_t _co2, const uint16_t _tvoc)
  : co2(_co2), tvoc(_tvoc)
{
}
