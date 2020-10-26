#include "ImGuiLayer.hpp"

namespace HYT
{
    void ImGuiLayer::init()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        
        auto & io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    }
}