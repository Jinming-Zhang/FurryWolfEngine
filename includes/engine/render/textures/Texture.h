#pragma once
#include <string>
#include "glad/glad.h"

namespace WEngine
{
  struct TextureLoadConfig
  {
    bool flipY = true;
    bool genMipmap = true;
    GLint clapMode = GL_REPEAT;
    GLint filterMode = GL_LINEAR;
    GLuint TextureType = GL_TEXTURE_2D;
    GLuint TexImageTarget = GL_TEXTURE_2D;
    GLuint TexParameteriTarget = GL_TEXTURE_2D;
  };

  /**
   * @brief Texture class is responsible for loading a texture image data and upload it to GPU.
   * It then holds the texture object Id returned and will unload the texture data upon destroyed.
   * Texture object cannot be copied, only move is allowed.
   *
   */
  class Texture
  {
  protected:
    unsigned int textureId;
    GLuint textureType;
    virtual void ConfigTexParameteri(const TextureLoadConfig &config);

  public:
    Texture();

    Texture(const Texture &texture) = delete;
    Texture &operator=(const Texture &texture) = delete;

    Texture(const Texture &&texture);
    Texture &operator=(Texture &&texture);

    void Destroy();
    virtual ~Texture();

    bool LoadTexture(const std::string &path, const TextureLoadConfig &config);
    void Use(int textureUnit);
    operator std::string() const;
  };
}
