#pragma once
#include <vector>
#include <memory>

namespace WEngine
{
  class GameObject;
  class WolfGlfwWindow;
  class PhongShader;
  class LightSourceShaderProgram;
  class Mesh;
  class VerticesMesh;
  class CameraComponent;

  class FurryWolfEngine
  {
    friend class SceneMaker;

  private:
    WolfGlfwWindow *window;
    std::vector<std::unique_ptr<GameObject>> gameobjects;
    PhongShader *phongShader;
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
    GameObject *CreateGameObject();

  private:
    void CreateScene();
  };
}
