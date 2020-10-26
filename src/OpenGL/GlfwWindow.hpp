#include "ogl_base.hpp"
#include <GLFW/glfw3.h>

/**
 * @brief OpenGL specific code
 * 
 */
namespace HYT::OpenGL
{
    /**
     * @brief An application window implementation based on GLFW
     * 
     */
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
        void post(Event e);

    private:
        GLFWwindow * m_nativeWindow;
    };
} // namespace HYT::OpenGL
