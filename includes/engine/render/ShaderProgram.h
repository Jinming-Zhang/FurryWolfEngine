#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
#include "engine/math/glm/glm.hpp"
#include "engine/render/Shader.h"
namespace WEngine
{
  /**
   * @brief WE ONLY NEED TO CREATE ONE INSTANCE FOR EACH TYPE OF SHADER PROGRAM.
   * The value of the variables in the shader will be set by materials that uses it!
   * 
   */
  class ShaderProgram
  {
  protected:
    unsigned int shaderProgramId;

    GLint getUniformLocation(const std::string &name) const;

  public:
    ShaderProgram(/* args */);
    void Initialize();
    void AddShader(Shader &shader);
    void LinkShaders();
    virtual void UseProgram() const;
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
    void SetVec3(const std::string &name, float x, float y, float z) const;
    void SetMat4(const std::string &name, glm::mat4 matrix);
    ~ShaderProgram();
  };
}
