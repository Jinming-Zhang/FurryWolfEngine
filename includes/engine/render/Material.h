#pragma once
#include "engine/math/glm/glm.hpp"

namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  class Material
  {
    friend class FurryWolfEngine;

  private:
    FurryWolfEngine *engine;

  protected:
    Material();
    class ShaderProgram *shaderToUse;

  public:
    void SetShader(ShaderProgram *shader) { shaderToUse = shader; }
    virtual void Use(GameObject *go);
    ~Material();
  };
}
