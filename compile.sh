#!/bin/bash

defs=""
while getopts vp flag
do
  case "${flag}" in
    v) defs="${defs}-DVERBOSE";;
    p) defs="${defs} -DPERFETTO";;
  esac
done

echo Defined Macros are: "${defs}"
g++ --std=c++17 -g -Wall $defs -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu -lGLEW -lglfw -lGL -lm -ldl 
# verbose
# g++ --std=c++17 -g -Wall -DPERFETTO -DVERBOSE -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu -lglfw -lGL -lm -ldl 

# g++ --std=c++17 -g -Wall -DPERFETTO -o ./build/prog -I./includes $(find src -type f -iname \*\.cpp -o -iname \*\.c) -L/lib/x86_64-linux-gnu -lglfw -lGL -lm -ldl 
