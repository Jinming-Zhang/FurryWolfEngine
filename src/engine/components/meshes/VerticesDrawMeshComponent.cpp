#include <vector>
#include "engine/render/meshes/VerticesDrawMesh.h"
#include "engine/components/meshes/VerticesDrawMeshComponent.h"
namespace WEngine
{
  VerticesDrawMeshComponent::VerticesDrawMeshComponent() { mesh = nullptr; }
  VerticesDrawMeshComponent::~VerticesDrawMeshComponent() {}
  void VerticesDrawMeshComponent::Init(const std::vector<Vertex> vertices)
  {
    if (mesh != nullptr)
    {
      delete mesh;
    }
    mesh = new VerticesDrawMesh();
    mesh->Init(vertices);
  }
  void VerticesDrawMeshComponent::Render(bool transparentPass)
  {
    material->Use(gameObject);
    DrawMeshOnly();
  }
  void VerticesDrawMeshComponent::DrawMeshOnly()
  {
    mesh->Draw();
  }
}
