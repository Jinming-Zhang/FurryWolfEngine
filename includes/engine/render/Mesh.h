#pragma once
namespace WEngine
{
  class Mesh
  {
  private:
    unsigned int vao;
    unsigned int vbo;

  public:
    Mesh(/* args */);
    void AssignVerticies(float *verticies, int count);
    void UseMesh();
    void Render();

    ~Mesh();
  };
}
