#include "CameraComponent.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "Game.h"
#include "Windowing/Window.h"

namespace RecyclingGame {

    glm::mat4 CameraComponent::getProjectionMatrix() const {
        Window* window = Game::getInstance()->getWindow();
        return glm::perspective(
            glm::radians(fov),
            static_cast<float>(window->getWidth()) / static_cast<float>(window->getHeight()),
            0.1f,
            100.0f);
    }
    
}
