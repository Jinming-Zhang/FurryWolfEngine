#pragma once
#include <vector>

#include "engine/render/meshes/Mesh.h"
namespace WEngine
{
  class IndexedDrawMesh : public Mesh
  {
  private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    unsigned int indicesCount;

  public:
    IndexedDrawMesh();
    virtual ~IndexedDrawMesh();
    virtual void Draw() override;
    bool Init(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
  };

}
