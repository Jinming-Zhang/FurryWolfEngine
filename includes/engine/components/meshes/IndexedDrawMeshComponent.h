#pragma once
#include <vector>
#include <iostream>
#include <memory>

#include "engine/render/meshes/IndexedDrawMesh.h"
#include "engine/components/meshes/MeshComponent.h"
#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/Texture.h"

namespace WEngine
{
  /**
   * @brief Mesh is the minimal render unit, its redered using index draw method.
   * So a Mesh would contain a list of vertices and indices.
   */
  class IndexedDrawMeshComponent : public MeshComponent
  {
  private:
    IndexedDrawMesh *mesh;
    std::vector<std::unique_ptr<Texture>> textures;

  public:
    IndexedDrawMeshComponent();
    bool Init(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
    virtual void Render() override;
    virtual ~IndexedDrawMeshComponent();
  };
}
