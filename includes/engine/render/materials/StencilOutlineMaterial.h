#pragma once
#include "engine/render/Material.h"

namespace WEngine
{
  class StencilOutlineMaterial : public Material
  {
  private:
    /* data */
  public:
    class Mesh *tmpMesh;
    StencilOutlineMaterial(/* args */);
    ~StencilOutlineMaterial();
    virtual void Use(GameObject *go) override;
  };
}
