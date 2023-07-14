#pragma once
#include <string>
#include <vector>
#include "glad/glad.h"
namespace WEngine
{
  class Shader
  {
  private:
    unsigned int shaderId;

  public:
    Shader();
    ~Shader();
    bool CompileShader(std::string path, GLenum shaderType);
    unsigned int GetId() const;
  };

}
