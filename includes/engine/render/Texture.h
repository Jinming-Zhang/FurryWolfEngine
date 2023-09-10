#pragma once
#include <string>
#include "glad/glad.h"

namespace WEngine
{
  struct TextureLoadConfig
  {
    bool flipY = true;
    GLint clapMode = GL_REPEAT;
  };

  /**
   * @brief Texture class is responsible for loading a texture image data and upload it to GPU.
   * It then holds the texture object Id returned and will unload the texture data upon destroyed.
   * Texture object cannot be copied, only move is allowed.
   *
   */
  class Texture
  {
  private:
    unsigned int textureId;

  public:
    Texture();
    Texture(const Texture &texture) = delete;
    Texture &operator=(const Texture &texture) = delete;
    Texture(const Texture &&texture);
    Texture &operator=(Texture &&texture);
    void Destroy();
    ~Texture();

    bool LoadTexture(const std::string &path, const TextureLoadConfig &config);
    void Use(int textureUnit);

    operator std::string() const;
  };
}
