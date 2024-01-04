#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <string>
#include <iostream>

#include "engine/render/textures/Texture.h"
#include "engine/render/ShaderProgram.h"

namespace WEngine
{
  enum class ShaderProgramType
  {
    Default,
    Phong,
    LightSource,
    DepthVisualizer,
    Outliner,
    SimpleUnlit,
    UIBasicScreen,
    CubemapSkybox
  };

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

    std::unordered_map<std::type_index, std::string> defaultResourcesPath;
    std::unordered_map<std::string, Resource<Texture>> textures;
    std::unordered_map<ShaderProgramType, std::unique_ptr<ShaderProgram>> shaders;

    void Init();
    ResourceManager();

  public:
    ~ResourceManager();
    static ResourceManager *Instance();

  public:
    // Resources
    template <typename T>
    const std::shared_ptr<T> LoadTexture(std::string path, TextureLoadConfig config = TextureLoadConfig{}, bool donotInitialize = false)
    {
      auto result = textures.find(path);
      if (result == textures.end())
      {
        std::shared_ptr<Texture> texture = std::make_shared<T>();
        if (!donotInitialize)
        {
          config.flipY = true;
          if (!texture->LoadTexture(path, config))
          {
            if (!texture->LoadTexture(defaultResourcesPath[typeid(Texture)], config))
            {
              std::cout << "Error loading texture and failed to load default texture!\n";
              return nullptr;
            }
          }
        }
        textures.insert({path, Resource<Texture>{texture, 0}});
      }
      ++textures.at(path).useCount;
      return std::static_pointer_cast<T>(textures.at(path).resource);
    }
    bool UnloadTexture(std::string path);
    ShaderProgram &GetShaderProgram(ShaderProgramType type);
    void PrintResourcesUsage();
  };
}
