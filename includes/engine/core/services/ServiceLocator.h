#pragma once
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <string>

#include "engine/core/services/IServiceProvider.h"

namespace WEngine {
    class ServiceLocator {
    private:
        static std::unordered_map<std::string, std::shared_ptr<IServiceProvider> > servicesMap;

    public:
        ServiceLocator() = delete;

        ~ServiceLocator() = delete;

        template<typename T>
        static void RegisterService(std::string key, T service) {
            // static_assert(std::is_base_of<IServiceProvider, std::remove_pointer<T>>::value, "T must inherit from IServiceProvider");
            if (!servicesMap.contains(key)) {
                printf("Registering service of  type: ");
                printf(key.c_str());
                printf("\n");
                servicesMap.insert(std::make_pair(key, service));
                // servicesMap[key] = service;
            }
        }

        template<typename T>
        static void SwapService(T service) {
        }

        template<typename T>
        static T GetService(std::string key) {
            // static_assert(std::is_base_of<IServiceProvider, std::remove_pointer<T>>::value, "T must inherit from IServiceProvider");
            if (servicesMap.contains(key)) {
                return (dynamic_cast<T>(servicesMap.at(key).get()));
            }
            printf("No Service Found\n");
            return nullptr;
        }

        static void Shutdown();
    };
}
