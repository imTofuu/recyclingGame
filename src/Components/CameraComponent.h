#pragma once
#include "TransformComponent.h"

#include <glm/mat4x4.hpp>

namespace RecyclingGame {

    struct CameraComponent {

        TransformComponent transform;
        float fov = 45.0f;

        glm::mat4 getProjectionMatrix() const;
        glm::mat4 getViewMatrix() const { return transform.getTransformationMatrix(); }
        
    };
    
}
