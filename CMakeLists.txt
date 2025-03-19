cmake_minimum_required(VERSION 3.30.5)

set(CMAKE_CXX_STANDARD 20)

project(recyclingGame)

add_subdirectory(lib)

add_executable(recyclingGame
        src/main.cpp
        src/Windowing/Window.cpp
        src/Windowing/Window.h
        src/Game.h
        src/Game.cpp
        src/Logger.cpp
        src/Logger.h
        src/Windowing/Renderer.cpp
        src/Windowing/Renderer.h
)

target_link_libraries(recyclingGame PRIVATE
        glad
        glfw
        glm
        boo
)
target_include_directories(recyclingGame PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/glad/include
        ${PROJECT_SOURCE_DIR}/lib/glfw/include
        ${PROJECT_SOURCE_DIR}/lib/glm
        ${PROJECT_SOURCE_DIR}/lib/boo/include
        ${PROJECT_SOURCE_DIR}/src
)