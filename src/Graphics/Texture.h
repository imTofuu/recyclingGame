#pragma once

namespace RecyclingGame {

    class Texture {
    public:

        Texture() : Texture(nullptr, 0, 0) {}
        Texture(const char* data, unsigned int width, unsigned int height);

        void remove();

        void setData(const char* data, unsigned int width, unsigned int height);

        void bind();

    private:

        unsigned int m_handle = 0;
        
    };
    
}