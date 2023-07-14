#pragma once
#include "engine/math/glm/glm.hpp"

#include "engine/render/PhongShader.h"
namespace WEngine
{
  class Mesh
  {
  private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int indicesCount;
    glm::mat4 transform;
    PhongShader *shaderToUse;

  public:
    bool wireframeMode = false;

  public:
    Mesh();
    void Init(float *verticies, int vCount, unsigned int *indices, int iCount);
    void Render();
    void SetTransform(glm::mat4 transform);
    void SetShader(PhongShader *shader);

    ~Mesh();
  };
}
