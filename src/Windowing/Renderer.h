#pragma once

#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Vector.h"

namespace RecyclingGame {

    class Renderer {
    public:
        
        void init();
        void render();

        void setAmbientStrength(float strength) { m_ambientStrength = strength; }
        void setAmbientColour(const Vector3& color) { m_ambientColor = color; }

    private:

        Shader* m_vertShader = nullptr, * m_fragShader = nullptr;
        ShaderProgram* m_shaderProgram = nullptr;

        Shader* m_lightVertShader = nullptr, * m_lightFragShader = nullptr;
        ShaderProgram* m_lightShaderProgram = nullptr;

        float m_ambientStrength = 0.1f;
        Vector3 m_ambientColor = Vector3(1.0f, 1.0f, 1.0f);
        
    };
    
}
