#pragma once

namespace RecyclingGame {

    class Shader;

    class ShaderProgram {
    public:

        ShaderProgram();

        void addShader(const Shader& shader);
        void use();
        
        [[nodiscard]] unsigned int getID() const { return m_handle; }

    private:

        unsigned int m_handle;
        
    };
    
}