#pragma once

#include "Core.hpp"
#include <imgui.h>

namespace HYT
{
    class ImGuiLayer : public Layer
    {
    public:
        virtual void init() override;
        virtual void onUpdate(float seconds) override;
        virtual void terminate() override;
        virtual void onEvent(Event &e) override;
    protected:
        void begin();
        void end();
    };
} // namespace HYT
