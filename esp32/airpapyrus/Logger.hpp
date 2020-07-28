#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <HardwareSerial.h>
#include "FilenameMacro.hpp"

namespace LoggerInternal
{
  template <typename ...Args>
  void Println(const char file[], const int line, const char function[], const Args &...args)
  {
    Serial.printf("[%s:%d %s()] ", file, line, function);
    Serial.println(args...);
  }

  template <typename ...Args>
  void Printf(const char file[], const int line, const char function[], const Args &...args)
  {
    Serial.printf("[%s:%d %s()] ", file, line, function);
    Serial.printf(args...);
    Serial.println();
  }
}

#define Println(...) LoggerInternal::Println(__FILENAME__, __LINE__, __func__, __VA_ARGS__)
#define Printf(...) LoggerInternal::Printf(__FILENAME__, __LINE__, __func__, __VA_ARGS__)

#endif
