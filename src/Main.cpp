#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/render/Mesh.h"
#include "engine/render/Texture.h"
#include "engine/render/ShaderProgram.h"

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

void LoadShaders(WEngine::ShaderProgram &sp)
{
  sp.Initialize();
  sp.AddShader("/home/wolf/Desktop/FurryWolfEngine/shaders/vertex.glsl", GL_VERTEX_SHADER);
  sp.AddShader("/home/wolf/Desktop/FurryWolfEngine/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
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
  WEngine::ShaderProgram sp;
  LoadShaders(sp);
  WEngine::TextureLoadConfig texLoadConfig1{};
  texLoadConfig1.flipY = false;
  texLoadConfig1.internalFormat = GL_RGB;
  texLoadConfig1.textureUnit = GL_TEXTURE0;
  WEngine::Texture texture;
  texture.LoadTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/container.jpg", texLoadConfig1);

  WEngine::Texture texture2;
  WEngine::TextureLoadConfig texLoadConfig2{};
  texLoadConfig2.flipY = true;
  texLoadConfig2.internalFormat = GL_RGBA;
  texLoadConfig2.textureUnit = GL_TEXTURE1;
  texture2.LoadTexture("/home/wolf/Desktop/FurryWolfEngine/assets/images/textures/awesomeface.png", texLoadConfig2);

  texture.Use(GL_TEXTURE0);
  texture2.Use(GL_TEXTURE1);
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
