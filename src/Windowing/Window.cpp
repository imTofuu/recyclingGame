#include "Window.h"

#include <chrono>

#include "Logger.h"

namespace RecyclingGame {

    static void keyChanged(GLFWwindow* window, int key, int scancode, int action, int mods) {
        auto* instance = static_cast<Window*>(glfwGetWindowUserPointer(window));
        instance->handleKeyChange(static_cast<Key>(key), action);
    }

    // Creates a window with a name and sets it as the current
    // context for OpenGL.
    Window::Window(const char* name) {
        m_window = glfwCreateWindow(
            640,
            480,
            name,
            nullptr,
            nullptr);

        glfwMakeContextCurrent(m_window);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetKeyCallback(m_window, keyChanged);
    }

    void Window::init() {
        m_renderer.init();
    }

    // Free memory associated with the window and destroy the GL context
    Window::~Window() {
        glfwDestroyWindow(m_window);
    }
    
    void Window::update() {

        // Render the current scene
        m_renderer.render();
        
        // GLFW uses multiple screen buffers to prevent screen
        // tearing by writing to one of the back buffers instead
        // of the one that is currently being shown
        glfwSwapBuffers(m_window);

        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        m_dt = currentTime - lastTime;
        lastTime = currentTime;
    }

    void Window::handleKeyChange(Key key, int action) {
        if (action == GLFW_PRESS) {
            m_keyListener.setKeyEnabledState(key, true);
        } else if (action == GLFW_RELEASE) {
            m_keyListener.setKeyEnabledState(key, false);
        }
    }


    unsigned int Window::getWidth() const {
        int width = 0;
        int _ = 0;
        glfwGetWindowSize(m_window, &width, &_);
        return width;
    }

    unsigned int Window::getHeight() const {
        int height = 0;
        int _ = 0;
        glfwGetWindowSize(m_window, &_, &height);
        return height;
    }

    
} 