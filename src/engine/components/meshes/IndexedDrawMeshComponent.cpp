#include "glad/glad.h"

#include "engine/components/meshes/IndexedDrawMeshComponent.h"

namespace WEngine
{
  IndexedDrawMeshComponent::IndexedDrawMeshComponent() { mesh = nullptr; }
  IndexedDrawMeshComponent::~IndexedDrawMeshComponent() {}

  bool IndexedDrawMeshComponent::Init(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices)
  {
    if (mesh != nullptr)
    {
      delete mesh;
    }
    mesh = new IndexedDrawMesh();
    return mesh->Init(vertices, indices);
  }

  void IndexedDrawMeshComponent::Render()
  {
    material->Use(gameObject);
    mesh->Draw();
  }
}
