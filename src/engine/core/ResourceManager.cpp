#include <iostream>
#include "engine/core/ResourceManager.h"
#include "engine/includeHeaders/TextureHeaders.h"

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
    TextureLoadConfig config;
    config.flipY = true;
    config.clapMode = GL_CLAMP_TO_EDGE;
    // load default texture path
    defaultResourcesPath[typeid(Texture)] =
        ("./assets/defaults/missing_texture.png");
    LoadTexture<Texture>("./assets/defaults/defaultTexture.png", config);
    // load default skybox cubemap texture
    config.filterMode = GL_LINEAR;
    config.flipY = true;
    config.genMipmap = false;
    config.TextureType = GL_TEXTURE_CUBE_MAP;
    config.TexParameteriTarget = GL_TEXTURE_CUBE_MAP;

    const std::shared_ptr<CubeMapTexture> defaultSkyboxCubemap = LoadTexture<CubeMapTexture>("defaultSkyboxCubemap", config, true);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_Z;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/front.jpg", config);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/back.jpg", config);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/right.jpg", config);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_X;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/left.jpg", config);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_Y;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/top.jpg", config);

    config.TexImageTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;
    defaultSkyboxCubemap->LoadTexture("./assets/defaults/cubemaps/skybox/bottom.jpg", config);

    // load shader programs
    // load and compile vertex shaders
    WEngine::Shader vertexShader{};
    vertexShader.CompileShader("./shaders/phongVert.vert", GL_VERTEX_SHADER);
    WEngine::Shader cubemapSkyboxVert{};
    cubemapSkyboxVert.CompileShader("./shaders/skybox/skyCube.vert", GL_VERTEX_SHADER);
    // load and compile fragment shaders
    WEngine::Shader cubemapSkyboxFrag{};
    cubemapSkyboxFrag.CompileShader("./shaders/skybox/skyCube.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader phongFrag{};
    phongFrag.CompileShader("./shaders/phongFrag.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader simpleUnlitFrag{};
    simpleUnlitFrag.CompileShader("./shaders/simpleUnlit.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader lightsourceFragmentShader{};
    lightsourceFragmentShader.CompileShader("./shaders/lightSourceFrag.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader depthVisualizerFragmentShader{};
    depthVisualizerFragmentShader.CompileShader("./shaders/depthVisualizer.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader outlinerFragmentShader{};
    outlinerFragmentShader.CompileShader("./shaders/outliner.frag", GL_FRAGMENT_SHADER);
    WEngine::Shader screenVertShader{};
    screenVertShader.CompileShader("./shaders/UI/UniversalVertexShader.vert", GL_VERTEX_SHADER);
    WEngine::Shader screenFragShader{};
    screenFragShader.CompileShader("./shaders/UI/BasicScreenFrag.frag", GL_FRAGMENT_SHADER);

    // link shaders into shader programs
    shaders = std::unordered_map<ShaderProgramType, std::unique_ptr<ShaderProgram>>{};

    std::unique_ptr<ShaderProgram> phongShader = std::make_unique<ShaderProgram>();
    phongShader->Initialize();
    phongShader->AddShader(vertexShader);
    phongShader->AddShader(phongFrag);
    phongShader->LinkShaders();
    shaders[ShaderProgramType::Phong] = std::move(phongShader);

    std::unique_ptr<ShaderProgram> simpleUnlitShader = std::make_unique<ShaderProgram>();
    simpleUnlitShader->Initialize();
    simpleUnlitShader->AddShader(vertexShader);
    simpleUnlitShader->AddShader(simpleUnlitFrag);
    simpleUnlitShader->LinkShaders();
    shaders[ShaderProgramType::SimpleUnlit] = std::move(simpleUnlitShader);

    std::unique_ptr<ShaderProgram> lightSourceSp = std::make_unique<ShaderProgram>();
    lightSourceSp->Initialize();
    lightSourceSp->AddShader(vertexShader);
    lightSourceSp->AddShader(lightsourceFragmentShader);
    lightSourceSp->LinkShaders();
    shaders[ShaderProgramType::LightSource] = std::move(lightSourceSp);

    std::unique_ptr<ShaderProgram> depthVisualizer = std::make_unique<ShaderProgram>();
    depthVisualizer->Initialize();
    depthVisualizer->AddShader(vertexShader);
    depthVisualizer->AddShader(depthVisualizerFragmentShader);
    depthVisualizer->LinkShaders();
    shaders[ShaderProgramType::DepthVisualizer] = std::move(depthVisualizer);

    std::unique_ptr<ShaderProgram> outlinerShaderProgram = std::make_unique<ShaderProgram>();
    outlinerShaderProgram->Initialize();
    outlinerShaderProgram->AddShader(vertexShader);
    outlinerShaderProgram->AddShader(outlinerFragmentShader);
    outlinerShaderProgram->LinkShaders();
    shaders[ShaderProgramType::Outliner] = std::move(outlinerShaderProgram);

    std::unique_ptr<ShaderProgram> screenShader = std::make_unique<ShaderProgram>();
    screenShader->Initialize();
    screenShader->AddShader(screenVertShader);
    screenShader->AddShader(screenFragShader);
    screenShader->LinkShaders();
    shaders[ShaderProgramType::UIBasicScreen] = std::move(screenShader);

    std::unique_ptr<ShaderProgram> skyboxCubeShader{std::make_unique<ShaderProgram>()};
    skyboxCubeShader->Initialize();
    skyboxCubeShader->AddShader(cubemapSkyboxVert);
    skyboxCubeShader->AddShader(cubemapSkyboxFrag);
    skyboxCubeShader->LinkShaders();
    shaders[ShaderProgramType::CubemapSkybox] = std::move(skyboxCubeShader);
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
