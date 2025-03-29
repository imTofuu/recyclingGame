#pragma once

namespace RecyclingGame {

    class ElementBuffer {
    public:

        ElementBuffer() : ElementBuffer(nullptr, 0) {}
        ElementBuffer(const void* data, unsigned int size);
        
        void remove();

        void setData(const void* data, unsigned int size);

        void bind();

        [[nodiscard]] bool hasExisted() const { return m_handle; }

    private:

        unsigned int m_handle;
        
    };
    
}