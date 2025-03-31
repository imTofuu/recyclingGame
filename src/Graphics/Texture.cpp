#include "Texture.h"

#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    // Generate a handle for a texture and put data on GPU memory
    Texture::Texture(const char *data, unsigned int width, unsigned int height) {
        glGenTextures(1, &m_handle);
        Logger::checkForGlError("Genning texture");
        bind();

        // Tell the GPU what to do if texture sample coordinates are outside the range 0 - 1.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Tell the GPU how to resample textures if they have to be scaled. GL_NEAREST results in
        // nearest neighbour sampling, which is a fast but low quality method which has jagged edges.
        // GL_LINEAR lerps the colour value which smoothens edges. Mipmapping is using smaller, lower
        // resolution textures for objects that are further away from the camera, which is a good way to
        // improve performance and reduce artifacts.
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        setData(data, width, height);
    }

    // Mark the texture for deletion
    void Texture::remove() {
        glDeleteTextures(1, &m_handle);
        Logger::checkForGlError( "Deleting texture");
    }

    // Bind the texture and allocate memory for the data
    void Texture::setData(const char *data, unsigned int width, unsigned int height) {
        bind();
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGBA,
            static_cast<int>(width),
            static_cast<int>(height),
            0,
            GL_RGBA,
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
