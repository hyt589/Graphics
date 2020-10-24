#include "opengl.hpp"

namespace HYT::OpenGL
{
    class OpenGLSandboxLayer : public Layer
    {
        virtual void init() override;
        virtual void onUpdate(float dt) override;
        virtual void terminate() override;
        virtual void onEvent(Event& e) override;
    };
} // namespace HYT::OpenGL
