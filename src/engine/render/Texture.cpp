#include <iostream>
#include "glad/glad.h"
#include "engine/util/stb_image.h"
#include "engine/render/Texture.h"

namespace WEngine
{
  Texture::Texture() {}
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
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    int width;
    int height;
    int nrChannels;
    stbi_set_flip_vertically_on_load(config.flipY);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    std::string imgExt = path.substr(path.find_last_of('.') + 1);
    GLint internalFormat;
    if (imgExt == "jpg")
    {
      internalFormat = GL_RGB;
    }
    else if (imgExt == "png")
    {
      internalFormat = GL_RGBA;
    }

    if (!data)
    {
      std::cout << "Error loading texture image: " << path << std::endl;
      glDeleteTextures(1, &textureId);
      glBindTexture(GL_TEXTURE_2D, 0);
      return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, config.clapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, config.clapMode);
    // texture filtering mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return true;
  }
  void Texture::Use(int textureUnit)
  {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
  }
  Texture::operator std::string() const
  {
    return std::to_string(textureId);
  }
}
