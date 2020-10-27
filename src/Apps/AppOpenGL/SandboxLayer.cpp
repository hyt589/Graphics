#include "SandboxLayer.hpp"

namespace HYT::OpenGL
{
    void SandboxLayer::init()
    {
        LOG_INFO("[SANDBOX] Layer initializing");

        subscribe(EventType::CursorPosEvent, [](Event& e)->bool
        {
            auto pos = std::any_cast<glm::vec2>(e.getData());
            return true;
        });

        
    }

    void SandboxLayer::onEvent(Event& e)
    {
        m_eventDispatcher.handle(e);
    }

    void SandboxLayer::terminate()
    {
        LOG_INFO("[SANDBOX] Layer terminating");
    }

    void SandboxLayer::onUpdate(float dt)
    {
        GL(glClearColor(0.1f, 0.3f, 0.9f, 1.f));
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
} // namespace HYT::OpenGL
