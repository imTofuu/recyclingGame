#pragma once

namespace RecyclingGame {

    struct MeshComponent {

        MeshComponent() { std::cout << "MeshComponent" << std::endl; }
        
        float* verticies = nullptr;
        unsigned int numVerticies = 0;
    };
    
}