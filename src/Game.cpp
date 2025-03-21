#include "Game.h"

#include <iostream>

#include "Logger.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"

namespace RecyclingGame {

    Game::Game() {

        // This lambda function will be called if GLFW encounters an error. This
        // helps reduce generic code for handling errors. This lambda function
        // logs the error code and description to std::cerr and adds a breakpoint
        // if you are running a debugger which you can then use to go through the
        // call stack and find the error.
        glfwSetErrorCallback([](int error, const char* description) {
            Logger::fatal(
                (std::to_string(error) +
                    std::string(" ") +
                    std::string(description)
                    ).c_str());
        });

        // Init GLFW, windowing library
        glfwInit();

        // These hints tell GLFW about the target environment for this code which
        // can solve some errors.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void Game::init() {
        
        auto window = Window("Recycling Game");

        // In this project, glad is built without a GL loader so we must
        // give it the GLFW loader.
        gladLoadGL(glfwGetProcAddress);

        // ReSharper disable once CppDFALocalValueEscapesFunction
        // m_window does not need to be a heap allocated object
        // since it will not be needed after the init function
        // (this will improve speed and reduce the risk of a memory
        // leak)
        m_window = &window;

        // Set the clear colour to black to be used when glClear is called
        glClearColor(0, 0, 0, 1);

        // This is the main loop of the game.
        while (window.isOpen()) {

            // Clear the back buffer
            glClear(GL_COLOR_BUFFER_BIT);

            float testSquareVerticies[] = {
                -0.5f, -0.5f, 0,
                0.5f, -0.5f, 0,
                0.5f, 0.5f, 0,
                0.5f, 0.5f, 0,
                -0.5f, 0.5f, 0,
                -0.5f, -0.5f, 0,
            };

            VertexBuffer vertexBuffer(testSquareVerticies, sizeof(testSquareVerticies));

            VertexArray vertexArray;
            vertexArray.setBuffer(0, vertexBuffer, { BufferLayout::ElementType::FLOAT3 });

            Shader vertShader("./../assets/Shaders/main.vert", Shader::ShaderType::VERT);
            Shader fragShader("./../assets/Shaders/main.frag", Shader::ShaderType::FRAG);

            ShaderProgram shaderProgram;
            shaderProgram.addShader(vertShader);
            shaderProgram.addShader(fragShader);
            shaderProgram.use();

            glDrawArrays(GL_TRIANGLES, 0, 6);
            
            glfwPollEvents();
            window.update();
        }
    }

    void Game::end() {
        // End glfw
        glfwTerminate();
    }
    
}
