#pragma once
#include "engine/math/glm/glm.hpp"

namespace WEngine
{
  class GameObject;
  class FurryWolfEngine;
  /**
   * @brief Material is a class that is used to set up the shader variables for a mesh.
   * Each subclass/type of material should have all the fields needed for the shader as member fields.
   */
  class Material
  {
    friend class FurryWolfEngine;

  private:
    FurryWolfEngine *engine;

  protected:
    Material();
    class ShaderProgram *shaderToUse;
    unsigned int renderPathNeeded = 1;

  public:
    void SetShader(ShaderProgram *shader) { shaderToUse = shader; }
    /**
     * @brief Use the material really means to set up the variables of the shader, such as different textures, model matrix, view matrix, etc.
     * Then the following draw call on mesh will use the variable values set up by the material.
     *
     * @param go
     */
    virtual void Use(GameObject *go);
    ~Material();
  };
}
