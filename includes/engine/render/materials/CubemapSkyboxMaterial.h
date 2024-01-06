#pragma once
#include "engine/render/Material.h"
#include "engine/includeHeaders/TextureHeaders.h"
#include <memory>
namespace WEngine
{
  class CubemapSkyboxMaterial : public Material
  {
  private:
    std::shared_ptr<CubeMapTexture> cubeMapTexture;

  public:
    CubemapSkyboxMaterial();
    ~CubemapSkyboxMaterial();
    virtual void Use(GameObject *go) override;
    void AssignCubemapTexture(std::shared_ptr<CubeMapTexture> texture);
  };
}
