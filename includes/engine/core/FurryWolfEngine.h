#pragma once
#include <vector>
#include <memory>
#include "engine/render/Material.h"

namespace WEngine
{
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

    Mesh *mesh1;
    Mesh *mesh2;
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
    GameObject *CreateGameObject();

  private:
    void CreateScene();
  };
}
