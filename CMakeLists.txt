cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(recyclingGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/recyclingGame)

add_subdirectory(assets)
add_subdirectory(lib)

add_executable(recyclingGame
        src/main.cpp
        src/Windowing/Window.cpp
        src/Windowing/Window.h
        src/Game.h
        src/Game.cpp
        src/Logger.cpp
        src/Logger.h
        src/Graphics/Vector.h
        src/Graphics/VertexBuffer.h
        src/Graphics/VertexBuffer.cpp
        src/Graphics/VertexArray.h
        src/Graphics/VertexArray.cpp
        src/Graphics/Shader.h
        src/Graphics/Shader.cpp
        src/Graphics/ShaderProgram.h
        src/Graphics/ShaderProgram.cpp
        src/Graphics/ElementBuffer.h
        src/Graphics/ElementBuffer.cpp
        src/Components/ModelComponent.h
        src/Components/TransformComponent.h
        src/Components/TransformComponent.cpp
        src/Components/CameraComponent.h
        src/Components/CameraComponent.cpp
        src/AssetFetcher.h
        src/Graphics/Mesh.h
        src/Graphics/Mesh.cpp
        src/AssetFetcher.cpp
        src/Graphics/Texture.h
        src/Graphics/Texture.cpp
        src/Windowing/Renderer.cpp
        src/Windowing/Renderer.h
        src/Components/LightComponent.h
        src/Graphics/Model.h
        src/Graphics/Model.cpp
)

add_compile_definitions(MAX_DRAW_LIGHTS=16)

add_dependencies(recyclingGame copy_assets)

target_link_libraries(recyclingGame PRIVATE
        glad
        glfw
        glm
        boo
        assimp
        stb
)

target_include_directories(recyclingGame PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/glad/include
        ${PROJECT_SOURCE_DIR}/lib/glfw/include
        ${PROJECT_SOURCE_DIR}/lib/glm
        ${PROJECT_SOURCE_DIR}/lib/boo/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/lib/assimp/include
        ${PROJECT_SOURCE_DIR}/lib/stb
)