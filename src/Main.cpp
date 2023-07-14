#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"

#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/render/Mesh.h"
#include "engine/render/Texture.h"
#include "engine/render/Shader.h"
#include "engine/render/PhongShader.h"

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

int main(int argc, char const *argv[])
{
  std::cout << "Wolf Engine\n";

  std::unique_ptr<IWindow> window{std::make_unique<WolfGlfwWindow>()};

  if (!window->Init(800, 600, "Fuck My Life"))
  {
    std::cout << "Error loading gl\n";
    return -1;
  }

  WEngine::PhongShader sp;
  LoadShaders(sp);

  WEngine::Mesh mesh;
  MakeMeshe(mesh);
  WEngine::Mesh mesh2;
  MakeMeshe(mesh2);

  mesh.SetShader(&sp);
  mesh2.SetShader(&sp);

  glm::mat4 model{1.f};
  model = glm::rotate(model, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});
  mesh.SetTransform(model);

  glm::mat4 model2{1.f};
  model2 = glm::scale(model2, glm::vec3(.5f, .5f, .5f));
  model2 = glm::rotate(model2, glm::radians(-55.f), glm::vec3{1.f, .0f, .0f});
  model2 = glm::translate(model2, glm::vec3{1.5f, 0.f, 0.f});
  mesh2.SetTransform(model2);

  while (!window->ShouldClose())
  {
    window->PollEvents();
    glClearColor(.2f, .3f, .3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view{1.f};
    view = glm::translate(view, glm::vec3(.0f, .0f, -3.f));

    glm::mat4 projection{1.f};
    projection = glm::perspective(glm::radians(45.f), 800.f / 600.f, .1f, 100.f);

    sp.SetView(view);
    sp.SetProjection(projection);

    mesh.Render();
    mesh2.Render();

    window->SwapBuffers();
  }

  return 0;
}
