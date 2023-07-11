#pragma once
namespace WEngine
{
  class Mesh
  {
  private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int indicesCount;

  public:
    bool wireframeMode = false;

  public:
    Mesh();
    void Init(float *verticies, int vCount, unsigned int *indices, int iCount);
    void Render();

    ~Mesh();
  };
}
