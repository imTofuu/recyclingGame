#include "Window.h"

#include <chrono>

namespace RecyclingGame {

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
    }

    // Free memory associated with the window and destroy the GL context
    Window::~Window() {
        glfwDestroyWindow(m_window);
    }
    
    void Window::update() {
        // GLFW uses multiple screen buffers to prevent screen
        // tearing by writing to one of the back buffers instead
        // of the one that is currently being shown
        glfwSwapBuffers(m_window);

        static std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        m_dt = std::chrono::duration<double>(currentTime - lastTime).count();
        lastTime = currentTime;
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