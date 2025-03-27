#pragma once
#include <glm/mat4x4.hpp>

#include "Graphics/Vector3.h"

namespace RecyclingGame {

    struct TransformComponent {

        Vector3 translation;
        Vector3 rotation;
        Vector3 scale { 1 };

        [[nodiscard]] glm::mat4 getTransformationMatrix() const;
    };
    
}
