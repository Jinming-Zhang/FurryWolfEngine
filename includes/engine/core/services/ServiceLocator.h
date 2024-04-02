#pragma once
namespace WEngine
{
  class ServiceLocator
  {
  private:
    /* data */
  public:
    ServiceLocator(/* args */);
    ~ServiceLocator();
    static void Init();

    template <typename T>
    static void RegisterService(T service)
    {
    }
    template <typename T>
    static void SwapService(T service)
    {
    }

    template <typename T>
    static T GetService()
    {
    }
  };
}
