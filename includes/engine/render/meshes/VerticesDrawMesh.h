#pragma once
#include <vector>
#include "engine/render/meshes/Mesh.h"

namespace WEngine
{
  class VerticesDrawMesh : public Mesh
  {
  protected:
    unsigned int vao;
    unsigned int vbo;
    unsigned int verticesCount;

  public:
    VerticesDrawMesh();
    virtual void Draw() override;
    virtual ~VerticesDrawMesh();

    bool Init(const std::vector<Vertex> &vertices);
  };
}
