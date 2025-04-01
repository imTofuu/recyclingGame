cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

project(recyclingGame)

add_subdirectory(lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/${PROJECT_NAME})

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
        src/Components/MeshComponent.h
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
)

target_link_libraries(recyclingGame PRIVATE
        glad
        glfw
        glm
        boo
        fast_obj_lib
        stb
)
target_include_directories(recyclingGame PUBLIC
        ${PROJECT_SOURCE_DIR}/lib/glad/include
        ${PROJECT_SOURCE_DIR}/lib/glfw/include
        ${PROJECT_SOURCE_DIR}/lib/glm
        ${PROJECT_SOURCE_DIR}/lib/boo/include
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/lib/fast_obj
        ${PROJECT_SOURCE_DIR}/lib/stb
)

add_custom_command(
        TARGET recyclingGame
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
