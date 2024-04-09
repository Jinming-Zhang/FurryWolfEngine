#include "engine/core/services/ServiceLocator.h"
#include <unordered_map>
#include <typeinfo>

namespace WEngine
{

  std::unordered_map<std::string, std::shared_ptr<IServiceProvider>> ServiceLocator::servicesMap{};
  void ServiceLocator::Shutdown()
  {
    servicesMap.clear();
  }
}
