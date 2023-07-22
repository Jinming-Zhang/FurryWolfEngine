#include <fstream>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/math/glm/gtc/type_ptr.hpp"

#include "engine/render/ShaderProgram.h"
#include "engine/util/Utils.h"

namespace WEngine
{
  ShaderProgram::ShaderProgram() {}
  ShaderProgram::~ShaderProgram() {}
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
    int location{getUniformLocation(name)};
    glUniform1i(location, (int)value);
  }
  void ShaderProgram::SetInt(const std::string &name, int value) const
  {
    int location{getUniformLocation(name)};
    glUniform1i(location, value);
  }
  void ShaderProgram::SetFloat(const std::string &name, float value) const
  {
    int location{getUniformLocation(name)};
    glUniform1f(location, value);
  }
  void ShaderProgram::SetVec3(const std::string &name, float x, float y, float z) const
  {
    int location{getUniformLocation(name)};
    glUniform3f(location, x, y, z);
  }
  void ShaderProgram::SetMat4(const std::string &name, glm::mat4 matrix)
  {
    int location{getUniformLocation(name)};
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
  }

  GLint ShaderProgram::getUniformLocation(const std::string &name) const
  {
    int location{glGetUniformLocation(shaderProgramId, name.c_str())};
    if (location == -1)
    {
#ifdef VERBOSE
      printf("ShaderProgram: Cannot locate location for uniform variable: [%s]\nIf the variable does exist in the shader, this could also happen if the variable is not used and stripped out by the compiler.\n", name.c_str());
#endif
#ifdef PERFETTO
      std::cout << "STRIKE FOR PERFECTION DETECTED! PROGRAM ABORTING!\n";
      abort();
#endif
    }
    return location;
  }
}
