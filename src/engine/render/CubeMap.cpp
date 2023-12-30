#include "engine/render/CubeMap.h"
#include "glad/glad.h"
#include "engine/core/ResourceManager.h"
namespace WEngine
{

  CubeMap::CubeMap() { glGenTextures(1, &textureId); }
  CubeMap::~CubeMap()
  {
    glDeleteTextures(1, &textureId);
    textureId = 0;
  }

  void CubeMap::LoadTexture(GLuint side, std::string path)
  {
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    ResourceManager::Instance()->LoadTexture(path);
  }
}
