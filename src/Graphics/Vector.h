#pragma once

namespace RecyclingGame {

    struct Vector3 {
        
        Vector3() : x(0), y(0), z(0) {}
        explicit Vector3(float scale) : x(scale), y(scale), z(scale) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        
        float x, y, z;
    };

    struct Vector2 {

        Vector2() : x(0), y(0) {}
        explicit Vector2(float scale) : x(scale), y(scale) {}
        Vector2(float x, float y) : x(x), y(y) {}

        float x, y;
        
    };
    
}