#include <vector>
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/SceneMaker.h"

#include "engine/core/GameObject.h"
#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/inputs/InputSystem.h"
#include "engine/render/Mesh.h"
#include "engine/render/VerticesMesh.h"
#include "engine/render/Texture.h"

#include "engine/render/Shader.h"
#include "engine/render/PhongShader.h"
#include "engine/render/LightSourceShaderProgram.h"
#include "engine/render/Material.h"
#include "engine/render/materials/PhongModelMaterial.h"

#include "engine/components/SpotLightComponent.h"
#include "engine/components/PointLightComponent.h"

#include "engine/components/CameraComponent.h"

#include "engine/components/TransformComponent.h"

namespace WEngine
{
  WEngineConfig FurryWolfEngine::engineConfig = WEngineConfig{4, 4};
  class TransformComponent;
  FurryWolfEngine::FurryWolfEngine()
  {
    gameobjects = std::vector<std::unique_ptr<GameObject>>();
  }

  FurryWolfEngine::~FurryWolfEngine() {}

  bool FurryWolfEngine::Init()
  {
    std::cout << "Wolf Engine\n";
    window = new WEngine::WolfGlfwWindow{};

    if (!window->Init(800, 600, "Fuck My Life"))
    {
      std::cout << "Error loading gl\n";
      return false;
    }

    WEngine::InputSystem::Instance()->SetWindowContext(window);
    WEngine::InputSystem::Instance()->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    LoadShaders();
    InitDefaultResources();

    return true;
  }

  void FurryWolfEngine::LoadShaders()
  {
    WEngine::Shader vertexShader{};
    vertexShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/phongVert.vert", GL_VERTEX_SHADER);

    WEngine::Shader fragmentShader{};
    fragmentShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/phongFrag.frag", GL_FRAGMENT_SHADER);

    WEngine::Shader lightsourceFragmentShader{};
    lightsourceFragmentShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/lightSourceFrag.frag", GL_FRAGMENT_SHADER);

    phongShader = new ShaderProgram();
    phongShader->Initialize();
    phongShader->AddShader(vertexShader);
    phongShader->AddShader(fragmentShader);

    phongShader->LinkShaders();

    lightSourceSp = new LightSourceShaderProgram();
    lightSourceSp->Initialize();
    lightSourceSp->AddShader(vertexShader);
    lightSourceSp->AddShader(lightsourceFragmentShader);
    lightSourceSp->LinkShaders();
  }

  void FurryWolfEngine::Start()
  {
    CreateScene();

    for (auto &go : gameobjects)
    {
      go->Awake();
    }
    for (auto &go : gameobjects)
    {
      go->Start();
    }
    glEnable(GL_DEPTH_TEST);
    float currTime{(float)glfwGetTime()};
    float prevTime = currTime;
    const float cap{1.f / 60.f};
    while (!window->ShouldClose())
    {
      currTime = glfwGetTime();
      if (currTime - prevTime < cap)
      {
        continue;
      }
      float delta = currTime - prevTime;
      prevTime = currTime;
      InputSystem::DeltaTime = delta;

      window->PollEvents();
      InputSystem::Instance()->Update();

      glClearColor(.2f, .3f, .3f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      phongShader->UseProgram();
      phongShader->SetInt("pLightsCount", PointLightComponent::PointLightIndexer);
      phongShader->SetInt("spLightsCount", SpotLightComponent::SpotLightIndexer);

      for (auto &go : gameobjects)
      {
        go->Update(delta);
        go->LateUpdate(delta);
      }
      camera->Update(delta);
      window->SwapBuffers();
    }
  }

  GameObject *FurryWolfEngine::CreateGameObject()
  {
    std::unique_ptr<GameObject> go{new GameObject()};
    go->AddComponent<TransformComponent>();
    go->engine = this;
    gameobjects.push_back(std::move(go));

    return gameobjects[gameobjects.size() - 1].get();
  }

  void FurryWolfEngine::CreateScene()
  {
    // SceneMaker::MakeLotsCubeScene(this);
    SceneMaker::MakeLightScene(this);
  }
  void FurryWolfEngine::InitDefaultResources()
  {
    WEngine::Shader vertexShader{};
    vertexShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/phongVert.vert", GL_VERTEX_SHADER);

    WEngine::Shader fragmentShader{};
    fragmentShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/phongFrag.frag", GL_FRAGMENT_SHADER);

    defaultShader = new PhongShader();
    defaultShader->Initialize();
    defaultShader->AddShader(vertexShader);
    defaultShader->AddShader(fragmentShader);
    defaultShader->LinkShaders();

    defaultMaterial = new PhongModelMaterial();
    defaultMaterial->SetObjColor(1.f, 192.f / 255.f, 203.f / 255.f);
    defaultMaterial->SetShader(defaultShader);
  }
}
