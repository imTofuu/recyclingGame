#pragma once

namespace RecyclingGame {

    class Shader;

    class ShaderProgram {
    public:

        ShaderProgram();

        void addShader(const Shader& shader);
        void use();

    private:

        unsigned int m_handle;
        
    };
    
}