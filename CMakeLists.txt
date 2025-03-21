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
        src/AssetManager.cpp
        src/AssetManager.h
        src/Graphics/Mesh.cpp
        src/Graphics/Mesh.h
        src/Graphics/Vector3.h
        src/Graphics/VertexBuffer.h
        src/Graphics/VertexBuffer.cpp
        src/Graphics/VertexArray.h
        src/Graphics/VertexArray.cpp
        src/Graphics/Shader.h
        src/Graphics/Shader.cpp
        src/Graphics/ShaderProgram.h
        src/Graphics/ShaderProgram.cpp
)

target_link_libraries(recyclingGame PRIVATE
        glad
        glfw
        glm
        boo
        fast_obj_lib
)
target_include_directories(recyclingGame PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/glad/include
        ${PROJECT_SOURCE_DIR}/lib/glfw/include
        ${PROJECT_SOURCE_DIR}/lib/glm
        ${PROJECT_SOURCE_DIR}/lib/boo/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/lib/fast_obj
)