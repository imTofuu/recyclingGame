#include "Texture.h"

#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    // Generate a handle for a texture and put data on GPU memory
    Texture::Texture(const char* data, unsigned int width, unsigned int height, TextureType type) {
        glGenTextures(1, &m_handle);
        Logger::checkForGlError("Genning texture");
        bind();

        // Tell the GPU what to do if texture sample coordinates are outside the range 0 - 1.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        Logger::checkForGlError("Setting texture wrap mode");

        // Tell the GPU how to resample textures if they have to be scaled. GL_NEAREST results in
        // nearest neighbour sampling, which is a fast but low quality method which has jagged edges.
        // GL_LINEAR lerps the colour value which smoothens edges. Mipmapping is using smaller, lower
        // resolution textures for objects that are further away from the camera, which is a good way to
        // improve performance and reduce artifacts.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Logger::checkForGlError("Setting texture filter mode");
        
        setData(data, width, height, type);
    }

    // Mark the texture for deletion
    void Texture::remove() {
        glDeleteTextures(1, &m_handle);
        Logger::checkForGlError( "Deleting texture");
    }

    // Bind the texture and allocate memory for the data
    void Texture::setData(const char *data, unsigned int width, unsigned int height, TextureType type) {
        int internalFormat = 0;
        int format = 0;
        switch (type) {
            case TextureType::COLOUR:
                internalFormat = GL_RGBA;
                format = GL_RGBA;
                break;
            case TextureType::DEPTH:
                internalFormat = GL_DEPTH_COMPONENT24;
                format = GL_DEPTH_COMPONENT;
                break;
            case TextureType::STENCIL:
                internalFormat = GL_STENCIL_INDEX8;
                format = GL_STENCIL_INDEX;
                break;
            case TextureType::DEPTH_STENCIL:
                internalFormat = GL_DEPTH24_STENCIL8;
                format = GL_DEPTH_STENCIL;
                break;
            default:
                Logger::error("Invalid texture type");
                internalFormat = GL_RGBA;
                format = GL_RGBA;
                break;
        }
        bind();
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            internalFormat,
            static_cast<int>(width),
            static_cast<int>(height),
            0,
            format,
            GL_UNSIGNED_BYTE,
            data);
        glGenerateMipmap(GL_TEXTURE_2D);
        Logger::checkForGlError("Setting texture data");
    }

    // Bind the texture so it can be used and its data can be set
    void Texture::bind() {
        glBindTexture(GL_TEXTURE_2D, m_handle);
        Logger::checkForGlError( "Binding texture");
    }

}
