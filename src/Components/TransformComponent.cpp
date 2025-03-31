#include "TransformComponent.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

namespace RecyclingGame {

    glm::mat4 TransformComponent::getTransformationMatrix() const {
        auto model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));
        auto rot =
            glm::toMat4(
            glm::quat(
                glm::vec3(
                    glm::radians(rotation.x),
                    glm::radians(rotation.y),
                    glm::radians(rotation.z)
                    )));
        model = glm::translate(model, glm::vec3(translation.x, translation.y, translation.z));
        model *= rot;
        return model;
    }

    
}
