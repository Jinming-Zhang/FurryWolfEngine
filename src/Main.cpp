#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/window/IWindow.h"
#include "engine/inputs/InputSystem.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/render/Mesh.h"
#include "engine/render/VerticesMesh.h"
#include "engine/render/Texture.h"
#include "engine/render/Shader.h"
#include "engine/render/PhongShader.h"
#include "engine/render/Camera.h"

void MakeMeshe(WEngine::Mesh &mesh);
void LoadShaders(WEngine::PhongShader &sp);
void MakeCubeMeshes(std::vector<WEngine::VerticesMesh *> &cubeMeshes, WEngine::PhongShader *shaderToUse);

int main(int argc, char const *argv[])
{
  std::cout << "Wolf Engine\n";

  std::unique_ptr<IWindow> window{std::make_unique<WEngine::WolfGlfwWindow>()};

  if (!window->Init(800, 600, "Fuck My Life"))
  {
    std::cout << "Error loading gl\n";
    return -1;
  }

  WEngine::InputSystem::Instance()->SetWindowContext(window.get());
  WEngine::InputSystem::Instance()->SetInputMode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  WEngine::PhongShader sp;
  LoadShaders(sp);

  WEngine::Mesh mesh;
  MakeMeshe(mesh);
  WEngine::Mesh mesh2;
  MakeMeshe(mesh2);

  mesh.SetShader(&sp);
  mesh2.SetShader(&sp);

  std::vector<WEngine::VerticesMesh *> vMeshes{};
  MakeCubeMeshes(vMeshes, &sp);

  glm::mat4 model{1.f};
  model = glm::rotate(model, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});
  mesh.SetTransform(model);

  glm::mat4 model2{1.f};
  model2 = glm::scale(model2, glm::vec3(.5f, .5f, .5f));
  model2 = glm::rotate(model2, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});
  model2 = glm::translate(model2, glm::vec3{1.5f, 0.f, 0.f});
  mesh2.SetTransform(model2);

  WEngine::Camera *camera{WEngine::Camera::Main()};
  camera->SetPosition(glm::vec3(.0f, .0f, 3.f));

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
    WEngine::InputSystem::DeltaTime = delta;

    window->PollEvents();
    WEngine::InputSystem::Instance()->Update();
    glClearColor(.2f, .3f, .3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera->Update(delta);
    sp.SetView(camera->GetClippedViewMatrix());
    for (auto vMesh : vMeshes)
    {
      vMesh->Update(delta);
      vMesh->Render();
    }
    // mesh.Render();
    // mesh2.Render();

    window->SwapBuffers();
  }

  return 0;
}

void MakeMeshe(WEngine::Mesh &mesh)
{
  float vertices[] = {
      // positions        // colors       // texture coordinates
      0.5f, 0.5f, 0.0f, 1.f, .0f, .0f, 1.f, 1.f,   // top right
      0.5f, -0.5f, 0.0f, .0f, 1.f, .0f, 1.f, 0.f,  // bottom right
      -0.5f, -0.5f, 0.0f, .0f, .0f, 1.f, 0.f, 0.f, // bottom left
      -0.5f, 0.5f, 0.0f, .5f, .5f, .5f, 0.f, 1.f   // top left
  };
  unsigned int indices[] = {
      // note that we start from 0!
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  mesh.Init(vertices, 32, indices, 6);
}

void LoadShaders(WEngine::PhongShader &sp)
{
  WEngine::Shader vShader{};
  vShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/vertex.glsl", GL_VERTEX_SHADER);

  WEngine::Shader fShader{};
  fShader.CompileShader("/home/wolf/Desktop/FurryWolfEngine/shaders/fragment.glsl", GL_FRAGMENT_SHADER);

  sp.Initialize();
  sp.AddShader(vShader);
  sp.AddShader(fShader);

  WEngine::TextureLoadConfig texLoadConfig1{};
  sp.AddAlbedoTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/container.jpg", texLoadConfig1);
  texLoadConfig1.flipY = true;
  texLoadConfig1.internalFormat = GL_RGBA;
  texLoadConfig1.textureUnit = GL_TEXTURE1;
  sp.AddAlbedoTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/awesomeface.png", texLoadConfig1);

  sp.LinkShaders();
}
void MakeCubeMeshes(std::vector<WEngine::VerticesMesh *> &cubeMeshes, WEngine::PhongShader *shaderToUse)
{
  float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

  glm::vec3 cubePositions[] = {
      glm::vec3(0.0f, 0.0f, 0.0f),
      glm::vec3(2.0f, 5.0f, -15.0f),
      glm::vec3(-1.5f, -2.2f, -2.5f),
      glm::vec3(-3.8f, -2.0f, -12.3f),
      glm::vec3(2.4f, -0.4f, -3.5f),
      glm::vec3(-1.7f, 3.0f, -7.5f),
      glm::vec3(1.3f, -2.0f, -2.5f),
      glm::vec3(1.5f, 2.0f, -2.5f),
      glm::vec3(1.5f, 0.2f, -1.5f),
      glm::vec3(-1.3f, 1.0f, -1.5f)};
  std::cout << sizeof(cubePositions) / sizeof(glm::vec3) << std::endl;
  for (size_t i{0}; i < 10; ++i)
  {
    glm::vec3 pos = cubePositions[i];
    WEngine::VerticesMesh *vMesh{new WEngine::VerticesMesh{vertices, 180}};
    vMesh->SetShader(shaderToUse);
    glm::mat4 transform{1.f};
    transform = glm::translate(transform, pos);
    transform = glm::rotate(transform, glm::radians(i * 20.f), glm::vec3(1.f, .3f, .5f));
    vMesh->SetTransform(transform);
    cubeMeshes.push_back(vMesh);
  }
}
