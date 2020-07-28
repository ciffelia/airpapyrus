#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace Constants {
  namespace Bluetooth {
    constexpr const char *SERVER_NAME = "airpapyrus";
  }

  namespace Serial {
    constexpr uint32_t SPEED = 115200;
  }

  namespace GPIO {
    // ピン番号
    namespace Pin
    {
      constexpr uint8_t I2C_SDA = 4;
      constexpr uint8_t I2C_SCL = 23;

      constexpr uint8_t CCS811_RESET = 25;
      constexpr uint8_t CCS811_WAKE = 26;
    }

    // I²C 7ビットアドレス
    namespace Address
    {
      constexpr uint8_t BME280 = 0x76;
      constexpr uint8_t CCS811 = 0x5B;
    }
  }
}

#endif
