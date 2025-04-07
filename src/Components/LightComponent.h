#pragma once

#include "Graphics/Vector.h"

namespace RecyclingGame {

    struct LightComponent {

        Vector3 colour = Vector3(1.0f);
        float intensity = 1.0f;
        int type = 0; // 0 = none, 1 = point, 2 = directional, 3 = spot
        
    };
    
}