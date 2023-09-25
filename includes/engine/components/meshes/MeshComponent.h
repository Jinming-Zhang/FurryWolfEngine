#pragma once
#include "engine/render/meshes/Mesh.h"
#include "engine/render/Material.h"
#include "engine/components/Component.h"

namespace WEngine
{
  /**
   * @brief `MeshComponent` is the base class for different types of mesh components, each will contain its own Mesh object that defines how to render the mesh.
   * @note `MeshComponent` contains the Material, hence the shader, about how the mesh will be rendered.
   *
   */
  class MeshComponent : public Component
  {
  protected:
    Material *material;

  public:
    MeshComponent();
    virtual ~MeshComponent();
    void SetMaterial(Material *mat) { material = mat; }
    Material *GetMaterial() { return material; }
    virtual void Render(bool transparentPass = false) = 0;
    virtual void DrawMeshOnly() = 0;
  };
}
