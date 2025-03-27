#include "TransformComponent.h"

#include <glm/ext/matrix_transform.hpp>

namespace RecyclingGame {

    glm::mat4 TransformComponent::getTransformationMatrix() const {
        auto model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
        // TODO: rotation
        model = glm::translate(model, glm::vec3(translation.x, translation.y, translation.z));
        return model;
    }

    
}
