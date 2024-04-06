#pragma once
#include <string>
#include "engine/core/services/ILogger.h"
namespace WEngine
{
  class Logger : public ILogger
  {
  private:
  public:
    Logger();
    virtual void Log(std::string msg) override;
    virtual void LogWarning(std::string msg) override;
    virtual void LogError(std::string msg) override;
    virtual ~Logger();
  };
}
