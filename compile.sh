#!/bin/bash
# g++ --std=c++17 -g -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu -lGLEW -lglfw -lGL -lm -ldl 
g++ --std=c++17 -g -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu -lglfw -lGL -lm -ldl 
