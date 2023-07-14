#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/render/Mesh.h"
#include "engine/render/Texture.h"
#include "engine/render/Shader.h"
#include "engine/render/PhongShader.h"

void MakeMeshes(WEngine::Mesh &mesh)
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

  WEngine::Mesh mesh;
  MakeMeshes(mesh);
  WEngine::PhongShader sp;
  LoadShaders(sp);

  WEngine::TextureLoadConfig texLoadConfig1{};
  sp.AddAlbedoTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/container.jpg", texLoadConfig1);
  texLoadConfig1.flipY = true;
  texLoadConfig1.internalFormat = GL_RGBA;
  texLoadConfig1.textureUnit = GL_TEXTURE1;
  sp.AddAlbedoTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/awesomeface.png", texLoadConfig1);

  while (!window->ShouldClose())
  {
    window->PollEvents();
    glClearColor(.2f, .3f, .3f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    sp.UseProgram();
    mesh.Render();

    window->SwapBuffers();
  }

  return 0;
}
