#pragma once

#include "Texture.h"

namespace RecyclingGame {

    class Framebuffer {
    public:

        Framebuffer();

        void remove();

        void attachColourAttachment(Texture& texture);
        void attachDepthAttachment(Texture& texture);
        void attachStencilAttachment(Texture& texture);
        void attachDepthStencilAttachment(Texture& texture);

        void bind();

    private:

        unsigned int m_handle;
        
    };

}
