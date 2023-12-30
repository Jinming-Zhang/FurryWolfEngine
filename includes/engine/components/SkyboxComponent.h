#pragma once
#include <memory>
#include <string>
#include <sstream>
#include "engine/components/Component.h"
#include "engine/includeHeaders/TextureHeaders.h"
#include "engine/includeHeaders/ResourceManagementHeaders.h"

namespace WEngine
{
  class SkyboxComponent
  {
  private:
    std::shared_ptr<Texture> cubemap;

  public:
    SkyboxComponent();
    ~SkyboxComponent();
    bool LoadSkyCubeFace(GLuint side, const std::string &path);
    void Render();
  };

}
