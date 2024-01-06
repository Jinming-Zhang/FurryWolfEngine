#include "engine/render/textures/CubeMapTexture.h"
#include <iostream>
#include "engine/util/stb_image.h"
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
  void CubeMapTexture::LoadCubemapTexture(GLuint side, std::string path)
  {
    textureType = GL_TEXTURE_CUBE_MAP;
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    int width;
    int height;
    int nrChannels;
    unsigned char *data;
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

    if (!data)
    {
      std::cout << "Error loading texture image: " << path << std::endl;
      stbi_image_free(data);
      return;
    }

    GLint internalFormat = nrChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(side, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
    // wrap mode
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // texture filtering mode
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  }
}
