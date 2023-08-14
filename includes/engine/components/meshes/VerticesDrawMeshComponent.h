#pragma once
#include <vector>

#include "engine/components/meshes/MeshComponent.h"
#include "engine/render/meshes/VerticesDrawMesh.h"
namespace WEngine
{
  class VerticesDrawMeshComponent : public MeshComponent
  {
  private:
    VerticesDrawMesh *mesh;

  public:
    VerticesDrawMeshComponent();
    virtual ~VerticesDrawMeshComponent();
    void Init(const std::vector<Vertex> vertices);
    virtual void Render() override;
  };
}
