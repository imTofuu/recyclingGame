#pragma once

namespace RecyclingGame {

    class VertexBuffer {
    public:

        VertexBuffer() : VertexBuffer(nullptr, 0) {}
        VertexBuffer(const void* data, unsigned int size);

        void remove();

        void setData(const void* data, unsigned int size);

        void bind();

    private:

        unsigned int m_handle = 0;
        
    };
    
}