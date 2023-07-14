#include <fstream>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/render/ShaderProgram.h"
#include "engine/util/Utils.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/math/glm/gtc/type_ptr.hpp"

namespace WEngine
{
  ShaderProgram::ShaderProgram() {}
  void ShaderProgram::Initialize()
  {
    shaderProgramId = glCreateProgram();
  }

  void ShaderProgram::AddShader(Shader &shader)
  {
    glAttachShader(shaderProgramId, shader.GetId());
  }

  void ShaderProgram::LinkShaders()
  {
    glLinkProgram(shaderProgramId);
    int success;
    char log[512];
    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success)
    {
      glGetProgramInfoLog(shaderProgramId, 512, NULL, log);
      std::cout << "Error linking shaders:\n\t" << log << std::endl;
      return;
    }
  }

  void ShaderProgram::UseProgram()
  {
    glUseProgram(shaderProgramId);
  }
  void ShaderProgram::SetBool(const std::string &name, bool value) const
  {
    int location{glGetUniformLocation(shaderProgramId, name.c_str())};
    if (location >= 0)
    {
      glUniform1i(location, (int)value);
    }
  }
  void ShaderProgram::SetInt(const std::string &name, int value) const
  {
    int location{glGetUniformLocation(shaderProgramId, name.c_str())};
    if (location >= 0)
    {
      glUniform1i(location, value);
    }
  }
  void ShaderProgram::SetFloat(const std::string &name, float value) const
  {
    int location{glGetUniformLocation(shaderProgramId, name.c_str())};
    if (location >= 0)
    {
      glUniform1f(location, value);
    }
  }
  ShaderProgram::~ShaderProgram() {}
}
