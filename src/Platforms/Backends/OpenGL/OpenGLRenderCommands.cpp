#include "OpenGLRenderCommands.hpp"

namespace HYT::OpenGL
{
    void RenderBackend::init() 
    {
        GL(glEnable(GL_BLEND));
		GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		GL(glEnable(GL_DEPTH_TEST));
    }
    
    void RenderBackend::setClearColor(float r, float g, float b, float a) 
    {
        LOG_TRACE("[OpenGL] Setting clear color: ({}, {}, {}, {})", r, g, b, a);
        GL(glClearColor(r, g, b, a));
    }
    
    void RenderBackend::clear(int bits) 
    {
        LOG_TRACE("[OpenGL] Clearing Color");
        GL(glClear(bits));
    }
    
    void RenderBackend::setViewPort(int x, int y, int width, int height) 
    {
        LOG_TRACE("[OpenGL] Setting viewport: ({}, {}, {}, {})", x, y, width, height);
        GL(glViewport(x, y, width, height));
    }
    
    void RenderBackend::drawIndexed(const Shared<::HYT::Graphics::VertexArray> &vertexArray, uint32_t count) 
    {
        uint32_t indexCount = count ? count : vertexArray->getIndexBuffer()->getCount();
        LOG_TRACE("[OpenGL] Drawing {} indexed elements", indexCount);
        GL(glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr));
        GL(glBindTexture(GL_TEXTURE_2D, 0));
    }


    
} // namespace HYT::OpenGL
