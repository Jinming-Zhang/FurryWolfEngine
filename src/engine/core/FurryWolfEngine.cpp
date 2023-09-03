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

    if (!window->Init(800, 600, "0w0"))
    {
      std::cout << "Error loading gl\n";
      return false;
    }

    WEngine::InputSystem::Instance()->SetWindowContext(window);
    // WEngine::InputSystem::Instance()->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return true;
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
    float currTime{(float)glfwGetTime()};
    float prevTime = currTime;
    const float cap{1.f / 60.f};
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
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
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      const ShaderProgram &phongShader = ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Phong);
      phongShader.UseProgram();
      phongShader.SetInt("pLightsCount", PointLightComponent::PointLightIndexer);
      phongShader.SetInt("spLightsCount", SpotLightComponent::SpotLightIndexer);

      for (auto &go : gameobjects)
      {
        go->Update(delta);
        go->LateUpdate(delta);
      }
      camera->Update(delta);

      for (auto &go : gameobjects)
      {
        go->Render();
      }

      window->SwapBuffers();
    }
  }

  GameObject *FurryWolfEngine::CreateGameObject(std::string name)
  {
    GameObject *go;
    if (name == "")
    {
      go = new GameObject();
    }
    else
    {
      go = new GameObject(name);
    }

    std::unique_ptr<GameObject> goPtr{go};
    goPtr->AddComponent<TransformComponent>();
    goPtr->engine = this;
    gameobjects.push_back(std::move(goPtr));

    return gameobjects[gameobjects.size() - 1].get();
  }

  void FurryWolfEngine::CreateScene()
  {
    // SceneMaker::MakeLotsCubeScene(this);
    // SceneMaker::MakeLightScene(this);
    SceneMaker::MakeDepthVisualizationScene(this);
  }
}
