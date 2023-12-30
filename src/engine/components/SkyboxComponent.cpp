#include "engine/components/SkyboxComponent.h"
namespace WEngine
{

  SkyboxComponent::SkyboxComponent()
  {
    const void *add = static_cast<const void *>(this);
    std::stringstream ss{};
    ss << add;
    cubemap = ResourceManager::Instance()->LoadTexture<CubeMapTexture>(
        ss.str(),
        WEngine::TextureLoadConfig{},
        true);
  }

  SkyboxComponent::~SkyboxComponent()
  {
  }

  bool SkyboxComponent::LoadSkyCubeFace(GLuint side, const std::string &path)
  {
    TextureLoadConfig config{};
    config.genMipmap = false;
    config.TextureType = GL_TEXTURE_CUBE_MAP;
    config.TexImageTarget = side;
    config.TexParameteriTarget = GL_TEXTURE_CUBE_MAP;
    config.clapMode = GL_CLAMP_TO_EDGE;
    config.flipY = true;
    return cubemap->LoadTexture(path, config);
  }
  void SkyboxComponent::Render()
  {
    cubemap->Use(GL_TEXTURE0);
  }

}
