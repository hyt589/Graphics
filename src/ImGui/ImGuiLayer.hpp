#pragma once

#include "Core.hpp"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace HYT
{
    class ImGuiLayer : public Layer
    {
        virtual void init() override;
        virtual void onUpdate(float seconds) override;
        virtual void terminate() override;
        virtual void onEvent(Event& e) override;
    };
} // namespace HYT
