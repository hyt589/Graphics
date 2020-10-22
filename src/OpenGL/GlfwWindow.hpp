#include "ogl_base.hpp"
#include <GLFW/glfw3.h>

namespace HYT::OpenGL
{
    class GlfwWindow : public Window
    {
    public:
        GlfwWindow(const WindowProps &props);
        ~GlfwWindow() override
        {
            
        };
        virtual void onUpdate() override;
        virtual void getSize(int &w, int &h) override;
        virtual void *GetNativeWindow() const override;

    private:
        GLFWwindow * m_nativeWindow;
    };
} // namespace HYT::OpenGL
