#pragma once
#include "engine/render/textures/Texture.h"

namespace WEngine
{
  class CubeMapTexture : public Texture
  {
  private:
    /* data */
  protected:
    virtual void ConfigTexParameteri(const TextureLoadConfig &config) override;

  public:
    CubeMapTexture();
    virtual ~CubeMapTexture();
  };
}
