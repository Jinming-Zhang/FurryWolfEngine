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

  void ResourceManager::Init()
  {
    // load default texture path
    defaultResourcesPath[typeid(Texture)] =
        ("./assets/defaults/missing_texture.png");

    // load shader programs
    // load and compile vertex shaders
    WEngine::Shader vertexShader{};
    vertexShader.CompileShader("./shaders/phongVert.vert", GL_VERTEX_SHADER);
    // load and compile fragment shaders
    WEngine::Shader fragmentShader{};
    fragmentShader.CompileShader("./shaders/phongFrag.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader lightsourceFragmentShader{};
    lightsourceFragmentShader.CompileShader("./shaders/lightSourceFrag.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader depthVisualizerFragmentShader{};
    depthVisualizerFragmentShader.CompileShader("./shaders/depthVisualizer.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader outlinerFragmentShader{};
    outlinerFragmentShader.CompileShader("./shaders/outliner.frag", GL_FRAGMENT_SHADER);

    // link shaders into shader programs
    std::unique_ptr<ShaderProgram> phongShader = std::make_unique<ShaderProgram>();
    phongShader->Initialize();
    phongShader->AddShader(vertexShader);
    phongShader->AddShader(fragmentShader);
    phongShader->LinkShaders();

    std::unique_ptr<ShaderProgram> lightSourceSp = std::make_unique<ShaderProgram>();
    lightSourceSp->Initialize();
    lightSourceSp->AddShader(vertexShader);
    lightSourceSp->AddShader(lightsourceFragmentShader);
    lightSourceSp->LinkShaders();

    std::unique_ptr<ShaderProgram> depthVisualizer = std::make_unique<ShaderProgram>();
    depthVisualizer->Initialize();
    depthVisualizer->AddShader(vertexShader);
    depthVisualizer->AddShader(depthVisualizerFragmentShader);
    depthVisualizer->LinkShaders();

    std::unique_ptr<ShaderProgram> outlinerShaderProgram = std::make_unique<ShaderProgram>();
    outlinerShaderProgram->Initialize();
    outlinerShaderProgram->AddShader(vertexShader);
    outlinerShaderProgram->AddShader(outlinerFragmentShader);
    outlinerShaderProgram->LinkShaders();

    shaders = std::unordered_map<ShaderProgramType, std::unique_ptr<ShaderProgram>>{};
    shaders[ShaderProgramType::Phong] = std::move(phongShader);
    shaders[ShaderProgramType::LightSource] = std::move(lightSourceSp);
    shaders[ShaderProgramType::DepthVisualizer] = std::move(depthVisualizer);
    shaders[ShaderProgramType::Outliner] = std::move(outlinerShaderProgram);
  }

  ResourceManager *ResourceManager::Instance()
  {
    if (instance == nullptr)
    {
      instance = new ResourceManager();
      instance->Init();
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

  ShaderProgram &ResourceManager::GetShaderProgram(ShaderProgramType type)
  {
    if (type == ShaderProgramType::Default)
    {
      return *shaders[ShaderProgramType::DepthVisualizer];
    }

    if (shaders.find(type) == shaders.end())
    {
      std::cout << "ResourceManager: GetShaderProgram failed, target shader program not in the map.\n";
      return *shaders[ShaderProgramType::Default];
    }
    else
    {
      return *(shaders[type]);
    }
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
