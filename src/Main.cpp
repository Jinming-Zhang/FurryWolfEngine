#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>

#include "engine/core/FurryWolfEngine.h"
#include "Main.h"

int main(const int argc, char const *argv[]) {
    std::string projectDir{"./"};
    if (argc >= 2) {
        projectDir = argv[1];
    }
    std::cout << "FurrywolfEngine, args: " << projectDir << "\n";
    Ravup(projectDir);
    return 0;
}

int Ravup(std::string path) {
    std::ifstream test{path};
    if (test) {
        std::filesystem::current_path(path);
    }
    std::cout << "Current working path: " << std::filesystem::current_path() << std::endl;

    WEngine::FurryWolfEngine engine{};
    engine.Init();
    engine.Start();
    engine.Reset();
    std::cout << "Engine Down...\n";
    return 0;
}
