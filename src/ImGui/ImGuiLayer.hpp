#pragma once

#include "Core.hpp"
#include <imgui.h>

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
