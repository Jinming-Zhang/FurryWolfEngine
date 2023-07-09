#include <fstream>
#include <iostream>
#include "glad/glad.h"
#include "engine/render/ShaderProgram.h"

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
    std::ifstream fin;
    fin.open(filePath, std::ios_base::openmode::_S_in);
    if (!fin.is_open())
    {
      std::cout << "Error openning shader file: " << filePath << std::endl;
      return;
    }
    std::string content;
    std::string line;
    while (getline(fin, line))
    {
      content.append(line);
      content.append("\n");
    }
    fin.close();

    unsigned int shaderId;
    shaderId = glCreateShader(shaderType);
    const char *shaderCode = content.c_str();

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
  }
  ShaderProgram::~ShaderProgram()
  {
  }
}
