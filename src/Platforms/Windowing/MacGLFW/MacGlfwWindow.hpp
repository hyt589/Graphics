#pragma once
#include "Core.hpp"
#include <GLFW/glfw3.h>

namespace HYT
{
    class MacGlfwWindow : public Window
    {
    public:
        MacGlfwWindow(const WindowProps & props, int glVerMajor = 4, int glVerMinor = 1);
        virtual ~MacGlfwWindow() override;

        virtual void onUpdate() override;
        virtual void getSize(int & w, int & h) override;
        virtual void* GetNativeWindow() const override;
        virtual Render::Context * getRenderContext() override;
        virtual void setRenderContext(Render::Context*) override;
        virtual void init() override;
        void post(Event e);

    private:
        GLFWwindow* m_nativeWindow;
    };
} // namespace HYT
