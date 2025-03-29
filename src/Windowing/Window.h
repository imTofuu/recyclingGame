#pragma once

#include <GLFW/glfw3.h>

namespace RecyclingGame {
    class Window {
    public:

        explicit Window(const char* name);
        ~Window();

        void update();
        
        [[nodiscard]] bool isOpen() const { return !glfwWindowShouldClose(m_window); }
        [[nodiscard]] double getDT() const { return m_dt; }

        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;

    private:

        double m_dt = 0;
        GLFWwindow* m_window;
        
    };
}
