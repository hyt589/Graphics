#include "SandboxLayer.hpp"
#include "OpenGL.hpp"

namespace HYT::OpenGL
{
    void SandboxLayer::init()
    {
        LOG_INFO("[SANDBOX] Layer initializing");

        subscribe(EventType::CursorPosEvent, [](Event &e) -> bool {
            LOG_TRACE("[SANDBOX] Processing cursor pos event");
            auto [x, y] = std::any_cast<std::pair<double, double>>(e.getData());
            return true;
        });

        subscribe(EventType::WindowResizeEvent, [](Event &e) -> bool {
            LOG_TRACE("[SANDBOX] Processing window resize event");
            auto [w, h] = std::any_cast<std::pair<int, int>>(e.getData());
            GL(glViewport(0, 0, (int)w, (int)h));
            return true;
        });
    }

    void SandboxLayer::onEvent(Event &e)
    {
        m_eventDispatcher.handle(e);
    }

    void SandboxLayer::terminate()
    {
        LOG_INFO("[SANDBOX] Layer terminating");
    }

    void SandboxLayer::onUpdate(float dt)
    {
        GL(glClearColor(0.1f, 0.1f, 0.1f, 1.f));
        GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    }
} // namespace HYT::OpenGL
