#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <string>

#include "engine/render/Texture.h"

namespace WEngine
{
  template <typename T>
  struct Resource
  {
    std::shared_ptr<T> resource;
    unsigned int useCount;
  };

  class ResourceManager
  {
  private:
    static ResourceManager *instance;

    std::unordered_map<std::string, Resource<Texture>> textures;
    std::unordered_map<std::type_index, std::string> defaultResourcesPath;

    ResourceManager();

  public:
    ~ResourceManager();
    static ResourceManager *Instance();
    const std::shared_ptr<Texture> LoadTexture(std::string path);
    bool UnloadTexture(std::string path);
    void PrintResourcesUsage();
  };
}
