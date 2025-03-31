#include "Game.h"

#include <iostream>

#include "Logger.h"
#include "Components/MeshComponent.h"
#include "Components/TransformComponent.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"
#include <glm/gtc/type_ptr.hpp>

#include "AssetFetcher.h"

namespace RecyclingGame {

    Game* Game::m_instance = nullptr;

    Game::Game() {

        // This lambda function will be called if GLFW encounters an error. This
        // helps reduce generic code for handling errors. This lambda function
        // logs the error code and description to std::cerr and adds a breakpoint
        // if you are running a debugger which you can then use to go through the
        // call stack and find the error.
        glfwSetErrorCallback([](int error, const char* description) {
            Logger::fatal(std::to_string(error) + std::string(" ") + std::string(description));
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
        Shader vertShader("./assets/Shaders/main.vert", Shader::ShaderType::VERT);
        Shader fragShader("./assets/Shaders/main.frag", Shader::ShaderType::FRAG);

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
        
        float testSquareVertices[] = {
            -0.5f, -0.5f, 0,
            0.5f, -0.5f, 0,
            0.5f, 0.5f, 0,
            -0.5f, 0.5f, 0,
        };

        float testSquareUVs[] = {
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f
        };

        unsigned int testSquareIndices[] = {
            0, 1, 2,
            2, 3, 0
        };

        msh->mesh.setVertices(testSquareVertices, sizeof(testSquareVertices) / sizeof(float) / 3);
        msh->mesh.setIndices(testSquareIndices, sizeof(testSquareIndices) / sizeof(unsigned int));

        VertexBuffer uvBuffer;
        uvBuffer.setData(testSquareUVs, sizeof(testSquareUVs));

        msh->mesh.setTexture(AssetFetcher::textureFromFile("./assets/texture.png"));
        msh->mesh.setBuffer(1, uvBuffer, BufferLayout::ElementType::FLOAT2);

        /*BOO::EntityID eid2 = m_scene.createEntity();
        BOO::ComponentRef<MeshComponent> msh2 = m_scene.addComponentToEntity<MeshComponent>(eid2);
        TransformComponent* tf2 = m_scene.addComponentToEntity<TransformComponent>(eid2);

        tf2->translation.z = -5.0f;

        msh2->mesh = AssetFetcher::meshFromOBJ("./assets/Suzanne.obj");*/

        // Disable vsync on the window so GLFW doesn't wait until the GPU is ready to swap buffers. This will require
        // a delta time to be used on physics and animations so the speed doesn't depend on the frame rate.
        glfwSwapInterval(0);
        
        // This is the main loop of the game.
        while (window.isOpen()) {

            // Clear the back buffer
            glClear(GL_COLOR_BUFFER_BIT);

            // Get the matrices associated with the camera. One of these is the projection matrix, which
            // can either be orthographic, where an object is always the same size regardless of distance
            // from the camera, or it can be perspective, where an object is smaller the further away it is.
            // It also has a view matrix which is similar to a model matrix but for the camera.
            auto projectionMatrix = getCamera()->getProjectionMatrix();
            auto viewMatrix = m_scene.entityHasComponent<TransformComponent>(getCamera().getEntity()) ? 
                m_scene.getComponentFromEntity<TransformComponent>(getCamera().getEntity())->getTransformationMatrix() :
                glm::mat4(1.0f);

            // Pre-multiply the camera matrices so it doesn't have to be done for every object.
            auto PVMatrix = projectionMatrix * viewMatrix;

            // Query for every object with a mesh in the scene and iterate through them.
            for (auto& [mesh] : m_scene.queryAll<MeshComponent>()) {

                // Default identity matrix in case the object doesn't have a transform component. An
                // identity matrix will not modify the other matrix when multiplied.
                auto modelMatrix = m_scene.entityHasComponent<MeshComponent>(mesh.getEntity()) ?
                    m_scene.getComponentFromEntity<TransformComponent>(mesh.getEntity())->getTransformationMatrix() :
                    glm::mat4(1.0f);

                if (auto tf = m_scene.getComponentFromEntity<TransformComponent>(mesh.getEntity())) {
                    tf->rotation.y += 0.01f;
                }

                // Bind the mesh for drawing
                mesh->mesh.bind();

                // Calculate the PVM matrix by multiplying the camera matrices with the model matrix.
                // The model matrix is the transformation matrix of the object, which when multiplied with
                // the model space vertices will convert it into world space. The PVMatrix will convert the
                // world space vertices into clip space.
                auto PVMMatrix = PVMatrix * modelMatrix;

                // Set the PVMMatrix as a uniform which can be accessed in the shader by declaring
                // a mat4 uniform named PVMMatrix.
                glUniformMatrix4fv(
                    glGetUniformLocation(shaderProgram.getID(), "PVMMatrix"),
                    1,
                    GL_FALSE,
                    glm::value_ptr(PVMMatrix));

                // Draw the bound mesh using the bound index buffer and vertex buffer.
                glDrawElements(
                    GL_TRIANGLES,
                    static_cast<int>(mesh->mesh.getNumVertices()),
                    GL_UNSIGNED_INT,
                    nullptr);
            }

            // GLFW polls events such as keyboard and mouse input. 
            glfwPollEvents();

            // The buffers are swapped and dt is calculated here.
            window.update();
        }
    }

    void Game::end() {
        // End glfw
        glfwTerminate();
    }
    
}
