#pragma once

namespace RecyclingGame {

    class Shader {
    public:

        enum class ShaderType {

            VERT,
            FRAG
            
        };
        
        Shader(const char* path, ShaderType type);
        ~Shader();
        
        [[nodiscard]] unsigned int tempgetHandle() const { return m_handle; }
        
    private:

        constexpr static unsigned int shaderType(ShaderType type);
        
        unsigned int m_handle;

        friend class ShaderProgram;
        
    };

}