#pragma once

#include <vector>
#include <string>
#include <memory>
#include "engine/render/Material.h"
#include "engine/core/ResourceManager.h"

namespace WEngine
{
  struct WEngineConfig
  {
    int MAX_POINT_LIGHTS;
    int MAX_SPOT_LIGHTS;
  };

  class GameObject;
  class WolfGlfwWindow;
  class Mesh;
  class VerticesMesh;
  class Material;
  class CameraComponent;

  class FurryWolfEngine
  {
    friend class SceneMaker;

  private:
    WolfGlfwWindow *window;
    std::vector<std::unique_ptr<GameObject>> gameobjects;
    CameraComponent *camera;

  public:
    FurryWolfEngine();
    ~FurryWolfEngine();
    bool Init();
    void Start();

  public:
    static WEngineConfig engineConfig;

  public:
    // resource creation methods
    template <typename T>
    T *CreateMaterial()
    {
      T *obj = new T();
      if (Material *mat = dynamic_cast<Material *>(obj))
      {
        mat->engine = this;
        mat->SetShader(&ResourceManager::Instance()->GetShaderProgram(ShaderProgramType::Default));
      }
      return obj;
    }
    GameObject *CreateGameObject(std::string name = "");

  private:
    void CreateScene();
  };
}
