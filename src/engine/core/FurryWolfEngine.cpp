#include <vector>
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"

#include "engine/core/FurryWolfEngine.h"
#include "engine/core/SceneMaker.h"
#include "engine/core/SceneManager.h"

#include "engine/core/Scene.h"
#include "engine/core/GameObject.h"
#include "engine/core/services/ServiceLocator.h"
#include "engine/core/services/ILogger.h"
#include "engine/core/services/Logger.h"

#include "engine/inputs/InputSystem.h"

#include "engine/render/FrameBuffer.h"
#include "engine/render/UI/ScreenQuad.h"
#include "engine/render/PhongShader.h"

#include "engine/components/SpotLightComponent.h"
#include "engine/components/PointLightComponent.h"
#include "engine/components/TransformComponent.h"

namespace WEngine
{
  WEngineConfig FurryWolfEngine::engineConfig = WEngineConfig{4, 4};
  class TransformComponent;
  FurryWolfEngine::FurryWolfEngine() : window{nullptr}
  {
    scenes = std::vector<Scene *>();
    State = EngineState();
  }

  FurryWolfEngine::~FurryWolfEngine()
  {
    glfwTerminate();
  }

  bool FurryWolfEngine::Init()
  {
    std::cout << "Wolf Engine\n";
    window = new WolfGlfwWindow{};

    if (!window->Init(800, 600, "0w0"))
    {
      std::cout << "Error loading gl\n";
      return false;
    }

    std::shared_ptr<IServiceProvider> logger = std::make_shared<Logger>();
    ServiceLocator::RegisterService(typeid(ILogger).name(), logger);
    ILogger *theLogger = ServiceLocator::GetService<ILogger *>(typeid(ILogger).name());
    if (theLogger != nullptr)
    {
      theLogger->Log("Logging Service Initialized");
    }
    else
    {
      std::cout << "No Logger Found\n";
    }

    InputSystem::Instance()->SetWindowContext(window);
#ifndef DEBUG
    InputSystem::Instance()->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);
#endif
    SceneManager::Init(this);
    SceneMaker::InitScenes(this);
    SceneManager::Instance().LoadScene(SceneMaker::GetSceneAt(0));
    return true;
  }

  void FurryWolfEngine::Start()
  {
    float currTime{(float)glfwGetTime()};
    float prevTime = currTime;
    const float cap{1.f / 60.f};
    glEnable(GL_DEPTH_TEST);

    ScreenQuad screenQuad{};
    FrameBuffer screenBuffer{window->GetWidth(), window->GetHeight()};

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

      screenBuffer.Use();
      glEnable(GL_DEPTH_TEST);
      glEnable(GL_BLEND);
      glClearColor(.2f, .3f, .3f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      // glEnable(GL_STENCIL_TEST);
      // glStencilMask(0xFF);
      // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

      for (auto scene : State.scenes)
      {
        scene->Refresh(delta);
      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glClearColor(.2f, .3f, .3f, 1.f);
      glClear(GL_COLOR_BUFFER_BIT);
      ShaderProgram screenShader = ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::UIBasicScreen);
      screenShader.UseProgram();
      screenShader.SetInt("screenTexture", 0);
      glDisable(GL_DEPTH_TEST);
      screenBuffer.UseTexture(GL_TEXTURE0);
      screenQuad.Render();

      window->SwapBuffers();
    }
  }

  void FurryWolfEngine::Reset()
  {
    PointLightComponent::Reset();
    SpotLightComponent::Reset();
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

    go->AddComponent<TransformComponent>();
    go->engine = this;
    return go;
  }

  void FurryWolfEngine::CreateScene()
  {
    // LoadScene(SceneMaker::MakeLotsCubeScene(this));
    // LoadScene(SceneMaker::MakeLightScene(this));
    // LoadScene(SceneMaker::MakeDepthVisualizationScene(this));
    // SceneManager::Instance().LoadScene(SceneMaker::MakeBlendingScene(this));
  }
}
