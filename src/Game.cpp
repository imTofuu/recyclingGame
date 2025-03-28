#include "Game.h"

#include <iostream>

#include "Logger.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/VertexArray.h"
#include "Graphics/VertexBuffer.h"
#include <glm/gtc/type_ptr.hpp>

namespace RecyclingGame {

    Game* Game::m_instance = nullptr;

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

        // ReSharper disable once CppDFALocalValueEscapesFunction
        // m_window does not need to be a heap allocated object
        // since it will not be needed after the init function
        // (this will improve speed and reduce the risk of a memory
        // leak)
        m_window = &window;

        // In this project, glad is built without a GL loader so we must
        // give it the GLFW loader.
        gladLoadGL(glfwGetProcAddress);

        // Set the clear colour to black to be used when glClear is called
        glClearColor(0, 0, 0, 1);

        // Read and compile shaders from a path.
        Shader vertShader("./../assets/Shaders/main.vert", Shader::ShaderType::VERT);
        Shader fragShader("./../assets/Shaders/main.frag", Shader::ShaderType::FRAG);

        // Attach the shaders to a shader program so they can be used
        ShaderProgram shaderProgram;
        shaderProgram.addShader(vertShader);
        shaderProgram.addShader(fragShader);
        shaderProgram.use();

        // Add a CameraComponent to the camera entity so the entity can actually
        // be used as a camera.
        m_scene.addComponentToEntity<CameraComponent>(m_cameraEntity);

        BOO::EntityID eid = m_scene.createEntity();
        BOO::ComponentRef<MeshComponent> msh = m_scene.addComponentToEntity<MeshComponent>(eid);
        TransformComponent* tf = m_scene.addComponentToEntity<TransformComponent>(eid);

        tf->translation.z = -5.0f;
        
        float testSquareVerticies[] = {
            -0.5f, -0.5f, 0,
            0.5f, -0.5f, 0,
            0.5f, 0.5f, 0,
            0.5f, 0.5f, 0,
            -0.5f, 0.5f, 0,
            -0.5f, -0.5f, 0,
        };
        
        msh->verticies = testSquareVerticies;
        msh->numVerticies = sizeof(testSquareVerticies) / sizeof(float);

        unsigned int frame = 0;

        // Disable vsync on the window so GLFW doesn't wait until the GPU is ready to swap buffers. This will require
        // a delta time to be used on physics and animations so the speed doesn't depend on the frame rate.
        glfwSwapInterval(1);
        
        // This is the main loop of the game.

        unsigned int frame = 0;
        
        while (window.isOpen()) {

            // Clear the back buffer
            glClear(GL_COLOR_BUFFER_BIT);

            auto PVMatrix = getCamera()->getProjectionMatrix() * getCamera()->getViewMatrix();

            BOO::QueryResult result = m_scene.queryAll<MeshComponent>();
            for (auto& [mesh] : result) {

                auto modelMatrix = glm::mat4(1.0f);

                if (TransformComponent* transform = m_scene.getComponentFromEntity<TransformComponent>(mesh.getEntity())) {
                    modelMatrix = transform->getTransformationMatrix();
                    transform->translation.x = sin(frame / 1000.0f);
                    transform->translation.y = cos(frame / 1000.0f);
                    transform->translation.z = -5 + sin(frame / 1000.0f);
                    frame++;
                }
                
                VertexBuffer vertexBuffer(mesh->verticies, mesh->numVerticies * sizeof(float));

                VertexArray vertexArray;
                vertexArray.setBuffer(0, vertexBuffer, { BufferLayout::ElementType::FLOAT3 });

                vertexArray.bind();

                auto pvm = PVMatrix * modelMatrix;

                glUniformMatrix4fv(
                    glGetUniformLocation(shaderProgram.getID(), "pvm"),
                    1,
                    GL_FALSE,
                    glm::value_ptr(pvm));

                glDrawArrays(GL_TRIANGLES, 0, mesh->numVerticies);
            }

            /*VertexBuffer vertexBuffer(testSquareVerticies, sizeof(testSquareVerticies));

            VertexArray vertexArray;
            vertexArray.setBuffer(0, vertexBuffer, { BufferLayout::ElementType::FLOAT3 });

            shaderProgram.use();

            glDrawArrays(GL_TRIANGLES, 0, 6);*/
            
            glfwPollEvents();
            window.update();
        }
    }

    void Game::end() {
        // End glfw
        glfwTerminate();
    }
    
}
