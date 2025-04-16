#include "Framebuffer.h"

#include <glad/gl.h>

#include "Logger.h"

namespace RecyclingGame {

    Framebuffer::Framebuffer() {
        glGenFramebuffers(1, &m_handle);
        Logger::checkForGlError("Genning framebuffer");
    }

    void Framebuffer::remove() {
        glDeleteFramebuffers(1, &m_handle);
        Logger::checkForGlError("Deleting framebuffer");
    }

    void Framebuffer::attachColourAttachment(Texture& texture) {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D,
            texture.m_handle,
            0);
        Logger::checkForGlError("Attaching colour attachment to framebuffer");
    }

    void Framebuffer::attachDepthAttachment(Texture &texture) {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER,
            GL_DEPTH_ATTACHMENT,
            GL_TEXTURE_2D,
            texture.m_handle,
            0);
        Logger::checkForGlError("Attaching depth attachment to framebuffer");
    }
    
    void Framebuffer::attachStencilAttachment(Texture &texture) {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER,
            GL_STENCIL_ATTACHMENT,
            GL_TEXTURE_2D,
            texture.m_handle,
            0);
        Logger::checkForGlError("Attaching stencil attachment to framebuffer");
    }

    void Framebuffer::attachDepthStencilAttachment(Texture &texture) {
        bind();
        glFramebufferTexture2D(GL_FRAMEBUFFER,
            GL_DEPTH_STENCIL_ATTACHMENT,
            GL_TEXTURE_2D,
            texture.m_handle,
            0);
        Logger::checkForGlError("Attaching depth stencil attachment to framebuffer");
    }
    
    void Framebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
        Logger::checkForGlError("Binding framebuffer");
    }
    
}
