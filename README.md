# Recycling Game

## Build
The project can be run either by downloading precompile binaries from the 
release page or by building it with CMake.

### Prerequisites
- A C++20 compiler such as clang or g++
- CMake 3.20 or higher to generate the makefiles
- git to fetch dependencies
- (For linux systems) Wayland dev libraries
- Python for project configuration
- jinja2 python package to build glad

Run run.sh to configure, build, and run the project. It does not work with 
zsh, the default Mac interpreter, so it must be run with an alternative like 
bash.

## Dependencies
- [BOO](https://github.com/imtofuu/boo) by me
- [glad](https://github.com/Dav1dde/glad) by Dav1dde
- [GLFW](https://github.com/glfw/glfw) by GLFW
- [GLM](https://github.com/g-truc/glm) by g-truc
- [stb](https://github.com/nothings/stb) by nothings
- [assimp](https://github.com/assimp/assimp) by assimp

They are all fetched as dependencies by CMake on configuration.