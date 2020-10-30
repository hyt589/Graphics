#include "ImGuiLayer.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include <GLFW/glfw3.h>

namespace HYT
{
    void ImGuiLayer::init()
    {

        LOG_INFO("[ImGui] Layer initializing");

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        auto &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow()), true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onEvent(Event &e)
    {
        m_eventDispatcher.handle(e);
    }

    void ImGuiLayer::onUpdate(float seconds)
    {
        begin();

        ImGui::Begin("Window");
        if (ImGui::Button("ClickMe"))
        {
            LOG_DEBUG("[ImGui] Button clicked");
            Graphics::Renderer::setAPI(GraphicsAPI::vulkan);
        }
        ImGui::End();

        end();
    }

    void ImGuiLayer::terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        LOG_INFO("[ImGui] Layer terminating");
    }

    void ImGuiLayer::begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
} // namespace HYT