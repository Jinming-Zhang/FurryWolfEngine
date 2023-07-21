#include <iostream>
#include "glad/glad.h"
#include "engine/util/stb_image.h"
#include "engine/render/Texture.h"

namespace WEngine
{
  Texture::Texture() {}
  Texture::~Texture() {}
  bool Texture::LoadTexture(const std::string& path, const TextureLoadConfig &config)
  {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    int width;
    int height;
    int nrChannels;
    stbi_set_flip_vertically_on_load(config.flipY);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (!data)
    {
      std::cout << "Error loading texture image: " << path << std::endl;
      return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, config.internalFormat, width, height, 0, config.internalFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
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
}
