#pragma once
#include <string>

#include "glad/glad.h"

namespace WEngine
{
  struct TextureLoadConfig
  {
    bool flipY = false;
  };

  class Texture
  {
  private:
    unsigned int textureId;

  public:
    Texture();
    Texture(const Texture &texture) = delete;
    Texture(Texture &&texture)
    {
      textureId = texture.textureId;
    }
    bool LoadTexture(const std::string &path, const TextureLoadConfig &config);
    void Use(int textureUnit);
    ~Texture();
  };
}
