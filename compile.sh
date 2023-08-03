#!/bin/bash

defs=""
while getopts vpd flag
do
  case "${flag}" in
    v) defs="${defs}-DVERBOSE";;
    p) defs="${defs} -DPERFETTO";;
    d) defs="${defs} -g -O0";;
  esac
done

echo Defined Macros are: "${defs}"
g++ --std=c++17 -Wall $defs -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu  -lGLEW -lglfw -lGL -lm -ldl -L./lib/linux/ -lassimp
