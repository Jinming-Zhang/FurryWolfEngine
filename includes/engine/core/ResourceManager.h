#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <string>

#include "engine/render/Texture.h"
#include "engine/render/ShaderProgram.h"

namespace WEngine
{
  enum class ShaderProgramType
  {
    Default,
    Phong,
    LightSource,
    DepthVisualizer,
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
    const std::shared_ptr<Texture> LoadTexture(std::string path);
    bool UnloadTexture(std::string path);
    ShaderProgram &GetShaderProgram(ShaderProgramType type);
    void PrintResourcesUsage();
  };
}
