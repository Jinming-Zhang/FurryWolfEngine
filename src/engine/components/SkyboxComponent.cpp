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
    skyboxMaterial = std::make_unique<CubemapSkyboxMaterial>();
    skyCubeMeshComponent = MeshComponentFactory::AddCubeMeshComponent(gameObject);
  }

  bool SkyboxComponent::LoadSkyCubeFace(GLuint side, const std::string &path)
  {
    // TextureLoadConfig config{};
    // config.genMipmap = false;
    // config.TextureType = GL_TEXTURE_CUBE_MAP;
    // config.TexImageTarget = side;
    // config.TexParameteriTarget = GL_TEXTURE_CUBE_MAP;
    // config.clapMode = GL_CLAMP_TO_EDGE;
    // config.flipY = true;
    return true;
    // return cubemap->LoadTexture(path, config);
  }

  void SkyboxComponent::Render(bool transparentPass)
  {
    glDepthMask(GL_FALSE);
    material->Use(gameObject);
    skyCubeMeshComponent->DrawMeshOnly();
    glDepthMask(GL_FALSE);
  }
  void SkyboxComponent::DrawMeshOnly()
  {
    skyCubeMeshComponent->DrawMeshOnly();
  }
}
