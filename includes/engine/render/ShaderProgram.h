#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
#include "engine/render/Shader.h"
namespace WEngine
{
  class ShaderProgram
  {
  protected:
    unsigned int shaderProgramId;

  public:
    ShaderProgram(/* args */);
    void Initialize();
    void AddShader(Shader &shader);
    void LinkShaders();
    virtual void UseProgram();
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    ~ShaderProgram();
  };
}
