#pragma once
#include <string>
namespace WEngine
{
  class ILogger
  {
  private:
    /* data */
  public:
    virtual void Log(std::string msg) = 0;
    virtual void LogWarning(std::string msg) = 0;
    virtual void LogError(std::string msg) = 0;
    virtual ~ILogger();
  };
}
