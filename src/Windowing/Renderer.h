#pragma once

#include "AssetFetcher.h"
#include "Graphics/Framebuffer.h"
#include "Graphics/Shader.h"
#include "Graphics/ShaderProgram.h"
#include "Graphics/Vector.h"

namespace RecyclingGame {

    class Renderer {
    public:
        
        void init();
        void render();

        void resize(int width, int height);

        void setAmbientStrength(float strength) { m_ambientStrength = strength; }

    private:

        Texture* m_mainColourTexture = nullptr, * m_mainDepthTexture = nullptr;
        Framebuffer* m_mainFramebuffer = nullptr;

        Shader* m_defaultFinalPassVert = nullptr, * m_defaultFinalPassFrag = nullptr;
        ShaderProgram* m_defaultFinalPassShaderProgram = nullptr;

        Shader* m_vertShader = nullptr, * m_fragShader = nullptr;
        ShaderProgram* m_shaderProgram = nullptr;

        Shader* m_lightVertShader = nullptr, * m_lightFragShader = nullptr;
        ShaderProgram* m_lightShaderProgram = nullptr;

        float m_ambientStrength = 0.1f;
        
    };
    
}
