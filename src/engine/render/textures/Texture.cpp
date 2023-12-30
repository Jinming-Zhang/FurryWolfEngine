#include <iostream>
#include "glad/glad.h"
#include "engine/util/stb_image.h"
#include "engine/render/textures/Texture.h"
#include "engine/util/ImageLoader.h"

namespace WEngine
{
  Texture::Texture()
  {
    glGenTextures(1, &textureId);
  }

  Texture::Texture(const Texture &&texture)
  {
    textureId = texture.textureId;
  }
  Texture &Texture::operator=(Texture &&texture)
  {
    if (this != &texture)
    {
      textureId = texture.textureId;
    }
    return *this;
  }
  void Texture::Destroy()
  {
    std::cout << "Texture " << textureId << " destroyed\n";
    glDeleteTextures(1, &textureId);
    textureId = 0;
  }
  Texture::~Texture()
  {
    std::cout << "Texture " << textureId << " destructor called\n";
    Destroy();
  }

  bool Texture::LoadTexture(const std::string &path, const TextureLoadConfig &config)
  {
    glBindTexture(config.TextureType, textureId);
    textureType = config.TextureType;
    ImageLoader::ImageLoaderConfig imgLoaderConfig;
    imgLoaderConfig.FlipY = config.flipY;
    ImageLoader loader{};
    if (!loader.LoadImage(path, imgLoaderConfig))
    {
      glBindTexture(textureType, 0);
      return false;
    }

    GLint internalFormat = loader.NRChannels() == 3 ? GL_RGB : GL_RGBA;

    glTexImage2D(config.TexImageTarget, 0, internalFormat, loader.Width(), loader.Height(), 0, internalFormat, GL_UNSIGNED_BYTE, loader.Data());

    if (config.genMipmap)
    {
      glGenerateMipmap(GL_TEXTURE_2D);
    }

    ConfigTexParameteri(config);
    glBindTexture(textureType, 0);
    return true;
  }

  void Texture::ConfigTexParameteri(const TextureLoadConfig &config)
  {
    // wrap mode
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_WRAP_S, config.clapMode);
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_WRAP_T, config.clapMode);

    // texture filtering mode
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(config.TexParameteriTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  }

  void Texture::Use(int textureUnit)
  {
    glActiveTexture(textureUnit);
    glBindTexture(textureType, textureId);
  }
  Texture::operator std::string() const
  {
    return std::to_string(textureId);
  }
}
