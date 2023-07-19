#include "engine/math/glm/gtc/type_ptr.hpp"
#include "engine/render/LightSourceShaderProgram.h"
namespace WEngine
{
  LightSourceShaderProgram::LightSourceShaderProgram() {}

  void LightSourceShaderProgram::UseProgram()
  {
    ShaderProgram::UseProgram();
  }
  LightSourceShaderProgram::~LightSourceShaderProgram() {}
}
