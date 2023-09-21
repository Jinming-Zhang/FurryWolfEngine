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
  class Scene;

  class FurryWolfEngine
  {
    friend class SceneMaker;
    friend class Scene;

  private:
    WolfGlfwWindow *window;
    std::vector<Scene *> scenes;

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
      }
      return obj;
    }

    GameObject *CreateGameObject(std::string name = "");
    void LoadScene(Scene *scene);

  private:
    void CreateScene();
  };
}
