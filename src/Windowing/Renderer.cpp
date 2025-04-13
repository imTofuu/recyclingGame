#include "Renderer.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

#include "AssetFetcher.h"
#include "Game.h"
#include "Logger.h"

#include "Components/CameraComponent.h"
#include "Components/LightComponent.h"
#include "Components/TransformComponent.h"
#include "Components/ModelComponent.h"

namespace RecyclingGame {

    void Renderer::init() {
        
        // Set the clear colour to black to be used when the screen is cleared
        glClearColor(0, 0, 0, 1);
        Logger::checkForGlError("Setting clear colour");

        // Cull faces that are not facing the camera to reduce frag shader calls. Backwards facing faces are determined
        // by the winding of the vertices, in this case clockwise.
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
        Logger::checkForGlError("Enabling culling");

        // Enable depth testing to prevent overwriting fragments that are closer to the camera.
        glEnable(GL_DEPTH_TEST);
        Logger::checkForGlError("Enabling depth testing");

        // Create and compile the shaders
        m_vertShader = new Shader("./assets/Shaders/main.vert", Shader::ShaderType::VERT);
        m_fragShader = new Shader("./assets/Shaders/main.frag", Shader::ShaderType::FRAG);

        m_lightVertShader = new Shader("./assets/Shaders/lightmain.vert", Shader::ShaderType::VERT);
        m_lightFragShader = new Shader("./assets/Shaders/lightmain.frag", Shader::ShaderType::FRAG);

        // Attach the shaders to a shader program so they can be used
        m_shaderProgram = new ShaderProgram();
        m_shaderProgram->addShader(*m_vertShader);
        m_shaderProgram->addShader(*m_fragShader);

        m_lightShaderProgram = new ShaderProgram();
        m_lightShaderProgram->addShader(*m_lightVertShader);
        m_lightShaderProgram->addShader(*m_lightFragShader);

        // Create test lights

        BOO::Registry& scene = Game::getInstance()->getScene();
        
        BOO::EntityID lightEntity1 = scene.createEntity();
        LightComponent* light1Component = scene.addComponentToEntity<LightComponent>(lightEntity1);
        light1Component->colour = Vector3(0, 0, 1);
        light1Component->type = 1; // Point light

        TransformComponent* transformComponent1 = scene.addComponentToEntity<TransformComponent>(lightEntity1);
        transformComponent1->scale = Vector3(0.5f);

        BOO::EntityID lightEntity2 = scene.createEntity();
        LightComponent* light2Component = scene.addComponentToEntity<LightComponent>(lightEntity2);
        light2Component->colour = Vector3(1, 0, 0);
        light2Component->type = 1; // Point light

        TransformComponent* transformComponent2 = scene.addComponentToEntity<TransformComponent>(lightEntity2);
        transformComponent2->scale = Vector3(0.5f);

        BOO::EntityID lightEntity3 = scene.createEntity();
        LightComponent* light3Component = scene.addComponentToEntity<LightComponent>(lightEntity3);
        light3Component->colour = Vector3(0, 1, 0);
        light3Component->type = 1; // Point light

        TransformComponent* transformComponent3 = scene.addComponentToEntity<TransformComponent>(lightEntity3);
        transformComponent3->scale = Vector3(0.5f);
        
        m_shaderProgram->use();

        m_shaderProgram->setFloat("u_ambientStrength", m_ambientStrength);
        m_shaderProgram->setFloats("u_ambientColour", reinterpret_cast<float*>(&m_ambientColor), 3);
        
    }

    void Renderer::render() {

        // Clear the back buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

        // Query for every object with a model in the scene and iterate through them.
        for (auto& [model] : scene.queryAll<ModelComponent>()) {

            TransformComponent* modelTransform = scene.getComponentFromEntity<TransformComponent>(model.getEntity());

            // Default identity matrix in case the object doesn't have a transform component. An
            // identity matrix will not modify the other matrix when multiplied.
            auto modelMatrix = modelTransform ? modelTransform->getTransformationMatrix() : glm::mat4(1.0f);

            // The model used to visualise lights.
            Model lightModel = AssetFetcher::getLightModel();
            
            unsigned int i = 0;
            for (auto& [light] : scene.queryAll<LightComponent>()) {
                TransformComponent* lightTransform = scene.getComponentFromEntity<TransformComponent>(light.getEntity());

                float emptyvec[] = {0, 0, 0};

                if (lightTransform) {
                    lightTransform->translation.x = cos(glfwGetTime() + (2 * i * 3.14 / 3)) * 3.0f;
                    lightTransform->translation.z = sin(glfwGetTime() + (2 * i * 3.14 / 3)) * 3.0f;
                }

                auto lightModelMatrix = lightTransform ? lightTransform->getTransformationMatrix() : glm::mat4(1.0f);
                auto lightPVM = PVMatrix * lightModelMatrix;

                m_lightShaderProgram->use();

                m_lightShaderProgram->setFloats("u_lightColour", reinterpret_cast<float*>(&light->colour), 3);
                m_lightShaderProgram->setMat4("u_PVMMatrix", glm::value_ptr(lightPVM));

                lightModel.draw();

                m_shaderProgram->use();

                m_shaderProgram->setFloats(("u_lightInfos[" + std::to_string(i) + "].position").c_str(),
                    lightTransform ? reinterpret_cast<float*>(&lightTransform->translation) : emptyvec, 3);
                m_shaderProgram->setFloats(("u_lightInfos[" + std::to_string(i) + "].direction").c_str(),
                    lightTransform ? reinterpret_cast<float*>(&lightTransform->rotation) : emptyvec, 3);
                m_shaderProgram->setFloats(("u_lightInfos[" + std::to_string(i) + "].colour").c_str(),
                    reinterpret_cast<float*>(&light->colour), 3);
                m_shaderProgram->setFloat(("u_lightInfos[" + std::to_string(i) + "].intensity").c_str(),
                    light->intensity);
                m_shaderProgram->setInt(("u_lightInfos[" + std::to_string(i) + "].type").c_str(),
                    light->type);
                
                i++;
                if (i == MAX_DRAW_LIGHTS) break;
            }

            m_shaderProgram->use();

            // Set the PVMatrix as a uniform which can be accessed in the shader by declaring
            // a mat4 uniform named u_PVMatrix.
            m_shaderProgram->setMat4("u_PVMatrix", glm::value_ptr(PVMatrix));
            m_shaderProgram->setMat4("u_modelMatrix", glm::value_ptr(modelMatrix));
            
            model->model.draw();
        }
        
    }

    
}
