#pragma once

#include <glm/mat4x4.hpp>

namespace RecyclingGame {

    struct CameraComponent {
        
        float fov = 45.0f;

        [[nodiscard]] glm::mat4 getProjectionMatrix() const;
        
    };
    
}
