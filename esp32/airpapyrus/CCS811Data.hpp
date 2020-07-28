#ifndef CCS811_DATA_HPP
#define CCS811_DATA_HPP

#include <cstdint>

struct CCS811Data {
  explicit CCS811Data(const uint16_t co2, const uint16_t tvoc);
  
  uint16_t co2;
  uint16_t tvoc;
};

#endif
