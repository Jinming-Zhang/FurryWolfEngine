#include "engine/render/Shader.h"
#include "engine/util/Utils.h"
namespace WEngine
{

  Shader::Shader() {}
  Shader::~Shader() { glDeleteShader(shaderId); }
  bool Shader::CompileShader(std::string path, GLenum shaderType)
  {
    shaderId = glCreateShader(shaderType);
    std::string codeStr = Utils::ReadFile(path).c_str();
    const char *shaderCode = codeStr.c_str();

    glShaderSource(shaderId, 1, &shaderCode, NULL);
    glCompileShader(shaderId);

    int success;
    char log[512];
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success)
    {
      glGetShaderInfoLog(shaderId, 512, NULL, log);
      std::cout << "Error compiling shader " << path << ":\n\t" << log << std::endl;
      return false;
    }
    return true;
  }
  unsigned int Shader::GetId() const
  {
    return shaderId;
  }

}
