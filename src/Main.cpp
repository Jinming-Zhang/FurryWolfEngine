#include <iostream>
#include <memory>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/window/IWindow.h"
#include "engine/window/WolfGlfwWindow.h"
#include "engine/render/Mesh.h"
#include "engine/render/ShaderProgram.h"

void MakeMeshes(WEngine::Mesh &mesh)
{
  // define vertex coordinate
  float vertices[] = {
      -0.5f,
      -0.5f,
      .0f,
      0.5f,
      -0.5f,
      .0f,
      0.f,
      0.5f,
      .0f,
  };
  mesh.AssignVerticies(vertices, 9);
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
