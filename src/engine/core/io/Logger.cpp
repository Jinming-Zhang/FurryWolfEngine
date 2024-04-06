#include <iostream>
#include "engine/core/services/Logger.h"

namespace WEngine
{
  Logger::Logger() {}
  Logger::~Logger() {}

  void Logger::Log(std::string msg)
  {
    std::cout << msg;
  }

  void Logger::LogWarning(std::string msg)
  {
    this->Log(msg);
  }

  void Logger::LogError(std::string msg)
  {
    this->Log(msg);
  }
}
