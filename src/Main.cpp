#include "engine/core/FurryWolfEngine.h"
#include "Main.h"

int main(int argc, char const *argv[])
{
  Ravup();
  return 0;
}

int Ravup()
{
  WEngine::FurryWolfEngine engine{};
  engine.Init();
  engine.Start();
}
