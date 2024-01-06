#pragma once
#include <memory>
#include <string>
#include <sstream>
#include "engine/components/Component.h"
#include "engine/includeHeaders/TextureHeaders.h"
#include "engine/render/Material.h"
#include "engine/components/meshes/MeshComponent.h"
#include "engine/render/materials/CubemapSkyboxMaterial.h"
#include "engine/includeHeaders/ResourceManagementHeaders.h"

namespace WEngine
{
  class SkyboxComponent : public MeshComponent
  {
  private:
    MeshComponent *skyCubeMeshComponent;

  public:
    SkyboxComponent();
    ~SkyboxComponent();
    virtual void Awake() override;
    virtual void Render(bool transparentPass = false) override;
    virtual void DrawMeshOnly() override;
  };

}
