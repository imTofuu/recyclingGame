#pragma once

#include <BOO/BOO.h>

// Glad must be included here, even though it is not used in this file
// because Window.h includes GLFW, which includes a gl.h file. glad's gl.h
// should be used instead.
#include <glad/gl.h>
#include "Windowing/Window.h"

namespace RecyclingGame {

    class Game {
    public:

        Game();
        ~Game() = default;

        void init();
        void end();

        BOO::Registry& getScene() { return m_scene; }
        Window* getWindow() { return m_window; }

    private:

        BOO::Registry m_scene;
        Window* m_window = nullptr;
        
    };
    
}
