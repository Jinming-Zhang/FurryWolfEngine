#include <iostream>
#include "engine/core/ResourceManager.h"

namespace WEngine
{

  ResourceManager *ResourceManager::instance = nullptr;
  ResourceManager::ResourceManager()
  {
    textures = std::unordered_map<std::string, Resource<Texture>>{};

    defaultResourcesPath = std::unordered_map<std::type_index, std::string>();
  }

  ResourceManager::~ResourceManager() {}

  ResourceManager *ResourceManager::Instance()
  {
    if (instance == nullptr)
    {
      instance = new ResourceManager();
      // load default resources
      instance->defaultResourcesPath[typeid(Texture)] =
          ("./assets/defaults/missing_texture.png");
    }
    return instance;
  }

  const std::shared_ptr<Texture> ResourceManager::LoadTexture(std::string path)
  {
    auto result = textures.find(path);
    if (result == textures.end())
    {
      std::shared_ptr<Texture> texture = std::make_shared<Texture>();
      TextureLoadConfig config;
      config.flipY = true;
      if (!texture->LoadTexture(path, config))
      {
        if (!texture->LoadTexture(defaultResourcesPath[typeid(Texture)], config))
        {
          std::cout << "Error loading texture and failed to load default texture!\n";
          return nullptr;
        }
      }
      textures.insert({path, Resource<Texture>{texture, 0}});
    }
    ++textures.at(path).useCount;
    return textures.at(path).resource;
  }

  bool ResourceManager::UnloadTexture(std::string path)
  {
    auto result = textures.find(path);
    if (result != textures.end())
    {
      Resource<Texture> rsc = result->second;
      --rsc.useCount;
      if (rsc.useCount <= 0)
      {
        rsc.resource->Destroy();
        textures.erase(path);
      }
      return true;
    }
    std::cout << "ResourceManager: UnloadTexture failed, target texture not in the map.\n";
    return false;
  }

  void ResourceManager::PrintResourcesUsage()
  {
    std::cout << "ResourceManager: Printing resources usage:\n";

    std::cout << "Textures usage:\n";
    for (auto &rsc : textures)
    {
      std::cout << "Texture Path: " << rsc.first << std::endl;
      std::cout << "Id: " << rsc.second.resource << "\tResource use count: " << rsc.second.useCount << "\tSharedPtr use count:" << rsc.second.resource.use_count() << std::endl;
    }
  }
}
