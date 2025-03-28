#pragma once

#include <GLFW/glfw3.h>

#include "Renderer.h"

namespace RecyclingGame {
    class Window {
    public:

        explicit Window(const char* name);
        ~Window();

        void update();
        
        [[nodiscard]] bool isOpen() const { return !glfwWindowShouldClose(m_window); }
        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;

    private:

        GLFWwindow* m_window;
        
    };
}
