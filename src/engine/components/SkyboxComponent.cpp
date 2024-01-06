#include "engine/components/SkyboxComponent.h"
#include "engine/render/materials/CubemapSkyboxMaterial.h"
#include "engine/core/MeshComponentFactory.h"
#include "glad/glad.h"

namespace WEngine
{

  SkyboxComponent::SkyboxComponent()
  {
  }
  SkyboxComponent::~SkyboxComponent() {}

  void SkyboxComponent::Awake()
  {
    material = new CubemapSkyboxMaterial();
    skyCubeMeshComponent = MeshComponentFactory::AddCubeMeshComponent(gameObject);
  }

  void SkyboxComponent::Render(bool transparentPass)
  {
    if (!transparentPass)
    {
      glDepthMask(GL_FALSE);
      material->Use(gameObject);
      skyCubeMeshComponent->DrawMeshOnly();
      glDepthMask(GL_TRUE);
    }
  }

  void SkyboxComponent::DrawMeshOnly()
  {
    skyCubeMeshComponent->DrawMeshOnly();
  }
}
