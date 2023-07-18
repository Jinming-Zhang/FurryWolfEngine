#include "engine/math/glm/gtc/type_ptr.hpp"
#include "engine/render/LightSourceShaderProgram.h"
namespace WEngine
{
  LightSourceShaderProgram::LightSourceShaderProgram() {}

  void LightSourceShaderProgram::UseProgram()
  {
    ShaderProgram::UseProgram();

    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "cameraMatrix"), 1, GL_FALSE, glm::value_ptr(view));

    GLint objectColorLocation = glGetUniformLocation(shaderProgramId, "objectColor");
    if (objectColorLocation != -1)
    {
      glUniform3f(objectColorLocation, objectColor.r, objectColor.g, objectColor.b);
    }

    GLint lightColorLocation = glGetUniformLocation(shaderProgramId, "lightColor");
    if (lightColorLocation != -1)
    {
      glUniform3f(lightColorLocation, lightColor.r, lightColor.g, lightColor.b);
    }
  }
  LightSourceShaderProgram::~LightSourceShaderProgram() {}
}
