#include "engine/render/textures/CubeMapTexture.h"
#include "glad/glad.h"

namespace WEngine
{

  CubeMapTexture::CubeMapTexture() : Texture() {}
  CubeMapTexture::~CubeMapTexture()
  {
    glDeleteTextures(1, &textureId);
  }

  void CubeMapTexture::ConfigTexParameteri(const TextureLoadConfig &config)
  {
    // wrap mode
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_WRAP_S, config.clapMode);
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_WRAP_T, config.clapMode);
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_WRAP_R, config.clapMode);

    // texture filtering mode
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_MIN_FILTER, config.filterMode);
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_MAG_FILTER, config.filterMode);
  }
}
