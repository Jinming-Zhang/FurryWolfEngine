#include <fstream>
#include <iostream>
#include <math.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "engine/render/ShaderProgram.h"
#include "engine/util/Utils.h"
#include "engine/math/glm/glm.hpp"
#include "engine/math/glm/gtc/matrix_transform.hpp"
#include "engine/math/glm/gtc/type_ptr.hpp"

namespace WEngine
{
  ShaderProgram::ShaderProgram(/* args */) {}
  void ShaderProgram::Initialize()
  {
    shaderIds = std::vector<unsigned int>();
    shaderProgramId = glCreateProgram();
  }

  void ShaderProgram::AddShader(std::string filePath, GLenum shaderType)
  {
    unsigned int shaderId;
    shaderId = glCreateShader(shaderType);
    std::string codeStr = Utils::ReadFile(filePath).c_str();
    const char *shaderCode = codeStr.c_str();

    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    int success;
    char log[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shaderId, 512, NULL, log);
      std::cout << "Error compiling shader " << filePath << ":\n\t" << log << std::endl;
      return;
    }
    glAttachShader(shaderProgramId, shaderId);
    shaderIds.push_back(shaderId);
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
    for (auto id : shaderIds)
    {
      glDeleteShader(id);
    }
    shaderIds.clear();
  }

  void ShaderProgram::UseProgram()
  {
    glUseProgram(shaderProgramId);

    float g{sinf(glfwGetTime()) / 2.f + .5f};
    int clrLocation{glGetUniformLocation(shaderProgramId, "ourColor")};
    glUniform4f(clrLocation, .0f, g, .5f, 1.f);
    glUniform1i(glGetUniformLocation(shaderProgramId, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgramId, "texture2"), 1);
    glUniform1f(glGetUniformLocation(shaderProgramId, "mixPct"), .2f);

    glm::mat4 transform{1.f};
    transform = glm::rotate(transform, glm::radians(-90.f), glm::vec3(.0f, .0f, 1.f));
    transform = glm::scale(transform, glm::vec3(.5f, .5f, .5f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramId, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
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
