#pragma once
#include <string>
#include "engine/core/services/IServiceProvider.h"
namespace WEngine
{
  class ILogger : public IServiceProvider
  {
  private:
    /* data */
  public:
    ILogger() {}
    virtual void Log(std::string msg) = 0;
    virtual void LogWarning(std::string msg) = 0;
    virtual void LogError(std::string msg) = 0;
    virtual ~ILogger() {}
  };
}
