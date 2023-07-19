#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
namespace WEngine
{
  class Utils
  {
  public:
    Utils() = delete;
    static std::string ReadFile(std::string path)
    {
      std::ifstream fin;
      fin.open(path);
      if (!fin.is_open())
      {
        return nullptr;
        printf("Invalid file path: %s\n", path.c_str());
        abort();
      }
      std::stringstream strstream;
      strstream << fin.rdbuf();
      fin.close();
      return strstream.str();
    }

    ~Utils() = delete;
  };
}
