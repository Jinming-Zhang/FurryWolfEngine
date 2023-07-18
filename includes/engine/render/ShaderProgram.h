#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
#include "engine/math/glm/glm.hpp"
#include "engine/render/Shader.h"
namespace WEngine
{
  class ShaderProgram
  {
  protected:
    unsigned int shaderProgramId;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

  public:
    ShaderProgram(/* args */);
    void Initialize();
    void AddShader(Shader &shader);
    void LinkShaders();
    virtual void UseProgram();
    void SetModel(glm::mat4 newModel) { model = newModel; }
    void SetView(glm::mat4 newView) { view = newView; }
    void SetProjection(glm::mat4 newProjection) { projection = newProjection; }
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    ~ShaderProgram();
  };
}
