#include "SandboxLayer.hpp"

namespace HYT::OpenGL
{
    void OpenGLSandboxLayer::init()
    {
        LOG_INFO("[SANDBOX] Layer initializing");
    }

    void OpenGLSandboxLayer::onEvent(Event& e)
    {
        m_eventDispatcher.handle(e);
    }

    void OpenGLSandboxLayer::terminate()
    {
        LOG_INFO("[SANDBOX] Layer terminating");
    }

    void OpenGLSandboxLayer::onUpdate(float dt)
    {
        GL(glClearColor(0.1f, 0.3f, 0.9f, 1.f));
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
} // namespace HYT::OpenGL
