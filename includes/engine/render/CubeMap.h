#pragma once
#include "engine/render/textures/Texture.h"
namespace WEngine
{
  class CubeMap
  {
  private:
    GLuint textureId;

  public:
    CubeMap();
    ~CubeMap();
    void LoadTexture(GLuint side, std::string path);
  };

}
