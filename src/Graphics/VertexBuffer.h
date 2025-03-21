#pragma once

namespace RecyclingGame {

    class VertexBuffer {
    public:

        VertexBuffer() : VertexBuffer(nullptr, 0) {}
        VertexBuffer(const void* data, unsigned int size);
        ~VertexBuffer();

        void setData(const void* data, unsigned int size);

        void bind();

        unsigned int tempGetHandle() { return m_handle; }

    private:

        unsigned int m_handle = 0;
        
    };
    
}