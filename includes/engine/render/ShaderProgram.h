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
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    ~ShaderProgram();
  };
}
