#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
namespace WEngine
{
  class ShaderProgram
  {
  private:
    unsigned int shaderProgramId;
    std::vector<unsigned int> shaderIds;

  public:
    ShaderProgram(/* args */);
    void Initialize();
    void AddShader(std::string filePath, GLenum shaderType);
    void LinkShaders();
    void UseProgram();
    ~ShaderProgram();
  };
}
