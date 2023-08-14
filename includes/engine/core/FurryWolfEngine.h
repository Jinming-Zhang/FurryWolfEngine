#pragma once

#include <vector>
#include <string>
#include <memory>
#include "engine/render/Material.h"

namespace WEngine
{
  struct WEngineConfig
  {
    int MAX_POINT_LIGHTS;
    int MAX_SPOT_LIGHTS;
  };

  class GameObject;
  class WolfGlfwWindow;
  class PhongShader;
  class ShaderProgram;
  class LightSourceShaderProgram;
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
    ShaderProgram *phongShader;
    LightSourceShaderProgram *lightSourceSp;

    CameraComponent *camera;

  private:
    void LoadShaders();

  public:
    FurryWolfEngine();
    ~FurryWolfEngine();
    bool Init();
    void Start();

  private:
    void InitDefaultResources();

  public:
    class PhongModelMaterial *defaultMaterial;
    PhongShader *defaultShader;
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
        mat->SetShader(phongShader);
      }
      return obj;
    }
    GameObject *CreateGameObject(std::string name = "");

  private:
    void CreateScene();
  };
}
