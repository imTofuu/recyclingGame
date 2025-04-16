#pragma once

#include <GLFW/glfw3.h>

#include "KeyListener.h"
#include "Renderer.h"

namespace RecyclingGame {
    
    class Window {
    public:

        explicit Window(const char* name);
        ~Window();

        void init();
        void update();

        void handleKeyChange(Key key, int action);
        void updateSize();
        
        [[nodiscard]] bool isOpen() const { return !glfwWindowShouldClose(m_window); }
        [[nodiscard]] double getDT() const { return m_dt; }

        [[nodiscard]] const KeyListener& getKeyListener() { return m_keyListener; }

        [[nodiscard]] unsigned int getWidth() const;
        [[nodiscard]] unsigned int getHeight() const;

    private:

        double m_dt = 0;
        GLFWwindow* m_window;

        KeyListener m_keyListener;

        Renderer m_renderer;
        
    };
}
