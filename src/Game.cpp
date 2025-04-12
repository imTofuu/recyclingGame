#include "Game.h"

#include <iostream>

#include "Logger.h"
#include "Components/ModelComponent.h"
#include "Components/TransformComponent.h"

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

        // In this project, glad is built without a GL loader so we must
        // give it the GLFW loader.
        gladLoadGL(glfwGetProcAddress);

        window.init();

        // ReSharper disable once CppDFALocalValueEscapesFunction
        // m_window does not need to be a heap allocated object
        // since it will not be needed after the init function
        // (this will improve speed and reduce the risk of a memory
        // leak)
        m_window = &window;

        // Initialise the light model since Model uses functions in its constructor
        // that require glad to be initialised.
        AssetFetcher::m_lightModel = new Model(AssetFetcher::modelFromPath("./assets/cube.obj"));

        // Add a CameraComponent to the camera entity so the entity can actually
        // be used as a camera.
        m_scene.addComponentToEntity<CameraComponent>(m_cameraEntity);
        TransformComponent* cameraTransform = m_scene.addComponentToEntity<TransformComponent>(m_cameraEntity);
        cameraTransform->translation = Vector3(0.0f, 0.0f, 10.0f);
        cameraTransform->rotation = Vector3(-10.0f, 0.0f, 0.0f);

        BOO::EntityID testEntity = m_scene.createEntity();
        BOO::ComponentRef<ModelComponent> testModel = m_scene.addComponentToEntity<ModelComponent>(testEntity);
        BOO::ComponentRef<TransformComponent> testTransform = m_scene.addComponentToEntity<TransformComponent>(testEntity);

        testModel->model = AssetFetcher::modelFromPath("./assets/Suzanne.obj");
        testModel->model.setTexture(0, AssetFetcher::textureFromFile("./assets/white.png"));

        // Disable vsync on the window so GLFW doesn't wait until the GPU is ready to swap buffers. This will require
        // a delta time to be used on physics and animations so the speed doesn't depend on the frame rate.
        glfwSwapInterval(0);
        
        // This is the main loop of the game.
        while (window.isOpen()) {
            
            // GLFW polls events such as keyboard and mouse input. 
            glfwPollEvents();

            // The game is rendered, buffers are swapped, and dt is calculated here.
            window.update();
        }
    }

    void Game::end() {
        // End glfw
        glfwTerminate();
    }
    
}
