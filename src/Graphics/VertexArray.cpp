#include "VertexArray.h"

#include <glad/gl.h>

namespace RecyclingGame {

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_handle);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_handle);
    }

    void VertexArray::bind() {
        glBindVertexArray(m_handle);
    }

    void VertexArray::setBuffer(unsigned int index, VertexBuffer& buffer, const BufferLayout& layout) {
        bind();
        buffer.bind();
        glVertexAttribPointer(
            index,
            elementsPerVertex(layout.elementType),
            elementType(layout.elementType),
            layout.normalise,
            layout.stride,
            nullptr);
        glEnableVertexAttribArray(index);
    }

    void VertexArray::setIBuffer(unsigned int index, VertexBuffer &buffer, const BufferLayout &layout) {
        bind();
        buffer.bind();
        glVertexAttribIPointer(
            index,
            elementsPerVertex(layout.elementType),
            elementType(layout.elementType),
            layout.stride,
            nullptr);
        glEnableVertexAttribArray(index);
    }

    void VertexArray::setLBuffer(unsigned int index, VertexBuffer &buffer, const BufferLayout &layout) {
        bind();
        buffer.bind();
        glVertexAttribLPointer(
            index,
            elementsPerVertex(layout.elementType),
            elementType(layout.elementType),
            layout.stride,
            nullptr);
        glEnableVertexAttribArray(index);
    }



    constexpr unsigned char VertexArray::elementsPerVertex(BufferLayout::ElementType elementType) {
        switch (elementType) {
            case BufferLayout::ElementType::BTYE:
            case BufferLayout::ElementType::UBYTE:
            case BufferLayout::ElementType::SHORT:
            case BufferLayout::ElementType::USHORT:
            case BufferLayout::ElementType::INT:
            case BufferLayout::ElementType::UINT:
            case BufferLayout::ElementType::FLOAT:
            case BufferLayout::ElementType::DOUBLE:
                return 1;
            case BufferLayout::ElementType::BYTE2:
            case BufferLayout::ElementType::UBYTE2:
            case BufferLayout::ElementType::SHORT2:
            case BufferLayout::ElementType::USHORT2:
            case BufferLayout::ElementType::INT2:
            case BufferLayout::ElementType::UINT2:
            case BufferLayout::ElementType::FLOAT2:
            case BufferLayout::ElementType::DOUBLE2:
                return 2;
            case BufferLayout::ElementType::BYTE3:
            case BufferLayout::ElementType::UBYTE3:
            case BufferLayout::ElementType::SHORT3:
            case BufferLayout::ElementType::USHORT3:
            case BufferLayout::ElementType::INT3:
            case BufferLayout::ElementType::UINT3:
            case BufferLayout::ElementType::FLOAT3:
            case BufferLayout::ElementType::DOUBLE3:
                return 3;
            case BufferLayout::ElementType::BYTE4:
            case BufferLayout::ElementType::UBYTE4:
            case BufferLayout::ElementType::SHORT4:
            case BufferLayout::ElementType::USHORT4:
            case BufferLayout::ElementType::INT4:
            case BufferLayout::ElementType::UINT4:
            case BufferLayout::ElementType::FLOAT4:
            case BufferLayout::ElementType::DOUBLE4:
                return 4;
        }
        return 0;
    }

    constexpr unsigned int VertexArray::elementType(BufferLayout::ElementType elementType) {
        switch (elementType) {
            case BufferLayout::ElementType::BTYE:
            case BufferLayout::ElementType::BYTE2:
            case BufferLayout::ElementType::BYTE3:
            case BufferLayout::ElementType::BYTE4:
                return GL_BYTE;
            case BufferLayout::ElementType::UBYTE:
            case BufferLayout::ElementType::UBYTE2:
            case BufferLayout::ElementType::UBYTE3:
            case BufferLayout::ElementType::UBYTE4:
                return GL_UNSIGNED_BYTE;
            case BufferLayout::ElementType::SHORT:
            case BufferLayout::ElementType::SHORT2:
            case BufferLayout::ElementType::SHORT3:
            case BufferLayout::ElementType::SHORT4:
                return GL_SHORT;
            case BufferLayout::ElementType::USHORT:
            case BufferLayout::ElementType::USHORT2:
            case BufferLayout::ElementType::USHORT3:
            case BufferLayout::ElementType::USHORT4:
                return GL_UNSIGNED_SHORT;
            case BufferLayout::ElementType::INT:
            case BufferLayout::ElementType::INT2:
            case BufferLayout::ElementType::INT3:
            case BufferLayout::ElementType::INT4:
                return GL_INT;
            case BufferLayout::ElementType::UINT:
            case BufferLayout::ElementType::UINT2:
            case BufferLayout::ElementType::UINT3:
            case BufferLayout::ElementType::UINT4:
                return GL_UNSIGNED_INT;
            case BufferLayout::ElementType::FLOAT:
            case BufferLayout::ElementType::FLOAT2:
            case BufferLayout::ElementType::FLOAT3:
            case BufferLayout::ElementType::FLOAT4:
                return GL_FLOAT;
            case BufferLayout::ElementType::DOUBLE:
            case BufferLayout::ElementType::DOUBLE2:
            case BufferLayout::ElementType::DOUBLE3:
            case BufferLayout::ElementType::DOUBLE4:
                return GL_DOUBLE;
        }
        return 0;
    }
    
}