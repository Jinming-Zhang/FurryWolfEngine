#include <iostream>
#include <vector>

#include "engine/core/FurryWolfEngine.h"

#include "engine/render/ShaderProgram.h"
#include "engine/render/PhongShader.h"
#include "engine/render/LightSourceShaderProgram.h"
class A
{
public:
  A *ap;
  A() {}
  ~A() {}
};

class B : public A
{
private:
  /* data */
public:
  B() {}
  ~B() {}
};

WEngine::ShaderProgram *mySp;
void SetShader(WEngine::ShaderProgram *sp)
{
  mySp = sp;
}
int main(int argc, char const *argv[])
{
  WEngine::FurryWolfEngine engine{};
  engine.Init();
  engine.Start();
  // WEngine::ShaderProgram *ap = new WEngine::ShaderProgram();
  // WEngine::LightSourceShaderProgram *childSp = new WEngine::LightSourceShaderProgram();
  // SetShader(childSp);
  // ap = phongSp;

  return 0;
}
