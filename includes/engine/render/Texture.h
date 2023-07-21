#pragma once
#include <string>
#include "glad/glad.h"
namespace WEngine
{
  struct TextureLoadConfig
  {
    bool flipY = false;
    GLint internalFormat = GL_RGB;
    GLenum textureUnit = GL_TEXTURE0;
  };

  class Texture
  {
  private:
    unsigned int textureId;

  public:
    Texture();
    bool LoadTexture(const std::string &path, const TextureLoadConfig &config);
    void Use(int textureUnit);
    ~Texture();
  };
}
