#pragma once
#include "Vector.h"

namespace RecyclingGame {

    struct Material {

        Vector3 ambientColour = Vector3(1.0f, 1.0f, 1.0f);
        Vector3 diffuseColour = Vector3(1.0f, 1.0f, 1.0f);
        Vector3 specularColour = Vector3(1.0f, 1.0f, 1.0f);
        float shininess = 32.0f;
        
    };
    
}
