#pragma once

#include "VertexBuffer.h"

namespace RecyclingGame {

    struct BufferLayout {

        enum class ElementType {
            BTYE, BYTE2, BYTE3, BYTE4,
            UBYTE, UBYTE2, UBYTE3, UBYTE4,
            SHORT, SHORT2, SHORT3, SHORT4,
            USHORT, USHORT2, USHORT3, USHORT4,
            INT, INT2, INT3, INT4,
            UINT, UINT2, UINT3, UINT4,

            FLOAT, FLOAT2, FLOAT3, FLOAT4,
            DOUBLE, DOUBLE2, DOUBLE3, DOUBLE4
        };

        BufferLayout(ElementType elementType)
            : BufferLayout(elementType, false, 0) {}
        BufferLayout(ElementType elementType, bool normalise, int stride)
            : elementType(elementType), normalise(normalise), stride(stride) {}
        
        ElementType elementType;
        bool normalise = false;
        int stride;
    };

    class VertexArray {
    public:

        VertexArray();

        void remove();

        void bind();
        
        void setBuffer(unsigned int index, VertexBuffer& buffer, const BufferLayout& layout);
        void setIBuffer(unsigned int index, VertexBuffer& buffer, const BufferLayout& layout);
        void setLBuffer(unsigned int index, VertexBuffer& buffer, const BufferLayout& layout);

    private:

        static constexpr unsigned char elementsPerVertex(BufferLayout::ElementType elementType);
        static constexpr unsigned int elementType(BufferLayout::ElementType elementType);

        unsigned int m_handle = 0;
        
    };
    
}
