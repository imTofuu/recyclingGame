#include "Renderer.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "Game.h"

#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MeshComponent.h"

namespace RecyclingGame {

    void Renderer::init() {
        
        // Set the clear colour to black to be used when glClear is called
        glClearColor(0, 0, 0, 1);

        // Create and compile the shaders
        m_vertShader = new Shader("./assets/Shaders/main.vert", Shader::ShaderType::VERT);
        m_fragShader = new Shader("./assets/Shaders/main.frag", Shader::ShaderType::FRAG);

        // Attach the shaders to a shader program so they can be used
        m_shaderProgram = new ShaderProgram();
        m_shaderProgram->addShader(*m_vertShader);
        m_shaderProgram->addShader(*m_fragShader);
        m_shaderProgram->use();

        glUniform1fv(
            glGetUniformLocation(m_shaderProgram->getID(), "u_ambientStrength"),
            1,
            &m_ambientStrength);
        glUniform3fv(
            glGetUniformLocation(m_shaderProgram->getID(), "u_ambientColour"),
            1,
            reinterpret_cast<float*>(&m_ambientColor));
    }

    void Renderer::render() {

        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT);

        auto camera = Game::getInstance()->getCamera();
        auto& scene = Game::getInstance()->getScene();

        // Get the matrices associated with the camera. One of these is the projection matrix, which
        // can either be orthographic, where an object is always the same size regardless of distance
        // from the camera, or it can be perspective, where an object is smaller the further away it is.
        // It also has a view matrix which is similar to a model matrix but for the camera.
        auto projectionMatrix = camera->getProjectionMatrix();
        auto viewMatrix = scene.entityHasComponent<TransformComponent>(camera.getEntity()) ? 
            scene.getComponentFromEntity<TransformComponent>(camera.getEntity())->getTransformationMatrix() :
            glm::mat4(1.0f);

        // Pre-multiply the camera matrices so it doesn't have to be done for every object.
        auto PVMatrix = projectionMatrix * viewMatrix;

        // Query for every object with a mesh in the scene and iterate through them.
        for (auto& [mesh] : scene.queryAll<MeshComponent>()) {

            // Default identity matrix in case the object doesn't have a transform component. An
            // identity matrix will not modify the other matrix when multiplied.
            auto modelMatrix = scene.entityHasComponent<MeshComponent>(mesh.getEntity()) ?
                scene.getComponentFromEntity<TransformComponent>(mesh.getEntity())->getTransformationMatrix() :
                glm::mat4(1.0f);

            if (auto tf = scene.getComponentFromEntity<TransformComponent>(mesh.getEntity())) {
                tf->rotation.y += 0.01f;
            }

            // Bind the mesh for drawing
            mesh->mesh.bind();

            // Set the PVMatrix as a uniform which can be accessed in the shader by declaring
            // a mat4 uniform named u_PVMatrix.
            glUniformMatrix4fv(
                glGetUniformLocation(m_shaderProgram->getID(), "u_PVMatrix"),
                1,
                GL_FALSE,
                glm::value_ptr(PVMatrix));

            glUniformMatrix4fv(
                glGetUniformLocation(m_shaderProgram->getID(), "u_modelMatrix"),
                1,
                GL_FALSE,
                glm::value_ptr(modelMatrix));

            // Draw the bound mesh using the bound index buffer and vertex buffer.
            glDrawElements(
                GL_TRIANGLES,
                static_cast<int>(mesh->mesh.getNumVertices()),
                GL_UNSIGNED_INT,
                nullptr);
            }
        
    }

    
}
