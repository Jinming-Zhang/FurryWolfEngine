# FurryWolfEngine
This is my personal on-going project with the goal of learning and practicing mordern C++, OpenGL, and various programming techniques such as design patterns, multi-threading, etc..
(Not really a game engine yet since there is no front-end scripting, but JFFun :))

## Planned stages of Furry Wolf Engine:
- Implement features listed in the FABULOUS Learn OpenGL website with a basic game engine structure, learn techniques of OpenGL <- Current Stage :)
- Practce Valgrind and make the code base memory leak free.
- Implement multi-threading for rendering passes.
- Refactor code into modules that can be exported and used as an simple game engine back end core.
- Create a front end graphical user interface that uses the game engine api to create simple games. (Language to be decided...)
- Implement a simple audio system.
- Implement or import a physics system.
- A pretty big plan already :). Hope I can get here one day!
    
### Latest Demo
The demo featuring a simple scene where you can navigate around by wasd key.
The scene contains the following objects:
- A directional light source (white cube)
- A imported guitar model
- A cube that attached with material that uses Phong shading model, and can blend up to 3 base textures and a base object color.
- A plane uses same material as the cube, with a high cyan object color.

Download the linux and windows built binary from [here](https://github.com/Jinming-Zhang/FurryWolfEngine/releases).
