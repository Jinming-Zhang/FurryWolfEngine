#include "engine/math/glm/gtc/type_ptr.hpp"
#include "engine/render/LightSourceShaderProgram.h"
namespace WEngine
{
  LightSourceShaderProgram::LightSourceShaderProgram() {}

  void LightSourceShaderProgram::UseProgram()const
  {
    ShaderProgram::UseProgram();
  }
  LightSourceShaderProgram::~LightSourceShaderProgram() {}
}
