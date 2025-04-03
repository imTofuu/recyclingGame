#pragma once

#include <GLFW/glfw3.h>

#include "Renderer.h"

namespace RecyclingGame {
    class Window {
    public:

        explicit Window(const char* name);
        ~Window();

        void init();
        void update();
        
        [[nodiscard]] bool isOpen() const { return !glfwWindowShouldClose(m_window); }
        [[nodiscard]] double getDT() const { return m_dt; }

        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;

    private:

        double m_dt = 0;
        GLFWwindow* m_window;

        Renderer m_renderer;
        
    };
}
