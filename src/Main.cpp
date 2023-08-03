#include "engine/core/FurryWolfEngine.h"

int main(int argc, char const *argv[])
{
  WEngine::FurryWolfEngine engine{};
  engine.Init();
  engine.Start();
  return 0;
}
