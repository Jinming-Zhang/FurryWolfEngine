#pragma once
#include <vector>
#include <iostream>
#include <memory>

#include "engine/render/materials/PhongModelMaterial.h"
#include "engine/render/Mesh.h"
#include "engine/render/Texture.h"

namespace WEngine
{
  /**
   * @brief Mesh is the minimal render unit, its redered using index draw method.
   * So a Mesh would contain a list of vertices and indices.
   */
  class IndexedDrawMeshComponent : public Mesh
  {
  private:
    unsigned int indicesCount;
    std::vector<std::unique_ptr<Texture>> textures;
    PhongModelMaterial *phongMat;

  public:
    IndexedDrawMeshComponent();
    bool Init(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices);
    virtual void Update(float deltaTime) override;
    virtual void Render() override;
    ~IndexedDrawMeshComponent();

  public:
    // getter setters
    void SetPhongMaterial(PhongModelMaterial *mat);
  };
}
