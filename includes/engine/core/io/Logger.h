#include <string>
namespace WEngine
{
  class Logger
  {
  private:
    /* data */
  public:
    Logger(/* args */);
    ~Logger();
    void Log(std::string msg);
    void LogWarning(std::string msg);
    void LogError(std::string msg);
  };

}
