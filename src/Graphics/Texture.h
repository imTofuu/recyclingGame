#pragma once

namespace RecyclingGame {

    enum class TextureType {
        COLOUR,
        DEPTH,
        STENCIL,
        DEPTH_STENCIL
    };

    class Texture {
    public:

        Texture() : Texture(nullptr, 0, 0) {}
        Texture(const char* data, unsigned int width, unsigned int height) : Texture(data, width, height, TextureType::COLOUR) {}
        Texture(const char* data, unsigned int width, unsigned int height, TextureType type);

        void remove();
        
        void setData(const char* data, unsigned int width, unsigned int height, TextureType type);

        void bind();

    private:

        unsigned int m_handle = 0;

        friend class Framebuffer;
        
    };
    
}