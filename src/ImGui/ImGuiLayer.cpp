#include "ImGuiLayer.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>

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

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        io.KeyMap[ImGuiKey_Tab] = HYT_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = HYT_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = HYT_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = HYT_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = HYT_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = HYT_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = HYT_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = HYT_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = HYT_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = HYT_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = HYT_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = HYT_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = HYT_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = HYT_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = HYT_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = HYT_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = HYT_KEY_A;
        io.KeyMap[ImGuiKey_C] = HYT_KEY_C;
        io.KeyMap[ImGuiKey_V] = HYT_KEY_V;
        io.KeyMap[ImGuiKey_X] = HYT_KEY_X;
        io.KeyMap[ImGuiKey_Y] = HYT_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = HYT_KEY_Z;
        io.FontGlobalScale = DPI_SCALE;

        // ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(APP_WINDOW->GetNativeWindow()), false);

        subscribe(EventType::MouseButtonPressEvent, [](Event &e) -> bool {
            auto mouseBtn = std::any_cast<int>(e.getData());

            if (mouseBtn == HYT_MOUSE_BUTTON_LEFT)
            {
                ImGui::GetIO().MouseDown[mouseBtn] = true;
                LOG_DEBUG("[ImGui] Event Handled: {}", e.to_string());
                return true;
            }

            return false;
        });

        subscribe(EventType::MouseButtonReleaseEvent, [](Event &e) -> bool {
            auto mouseBtn = std::any_cast<int>(e.getData());

            if (mouseBtn == HYT_MOUSE_BUTTON_LEFT)
            {
                ImGui::GetIO().MouseDown[mouseBtn] = false;
                LOG_DEBUG("[ImGui] Event Handled: {}", e.to_string());
                return true;
            }

            return false;
        });

        subscribe(EventType::CursorPosEvent, [](Event &e) -> bool {
            auto pos = std::any_cast<glm::vec2>(e.getData());
            ImGui::GetIO().MousePos = ImVec2(pos.x * DPI_SCALE, pos.y * DPI_SCALE);
            return false;
        });

        subscribe(EventType::WindowResizeEvent, [](Event &e) -> bool 
        {
            auto size = std::any_cast<glm::vec2>(e.getData());
            ImGui::GetIO().DisplaySize = ImVec2(size.x, size.y);
            LOG_DEBUG("[IMGUI] Window resized: {}×{}", (int)size.x, (int)size.y);
            return false;
        });

        int w, h;
        APP_WINDOW->getSize(w, h);
        w *= DPI_SCALE;
        h *= DPI_SCALE;
        LOG_DEBUG("Display Size: {} × {}", w, h);
        ImGui::GetIO().DisplaySize = ImVec2(w, h);
        ImGui_ImplOpenGL3_Init("#version 410");

    }

    void ImGuiLayer::onEvent(Event &e)
    {
        m_eventDispatcher.handle(e);
    }

    void ImGuiLayer::onUpdate(float seconds)
    {
        ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Window");
        if (ImGui::Button("ClickMe"))
        {
            LOG_DEBUG("clicked");
        }
        ImGui::End();

        // int w, h;
        // APP_WINDOW->getSize(w, h);
        // w *= RETINA_SCALE;
        // h *= RETINA_SCALE;
        // ImGui::GetIO().DisplaySize = ImVec2(w, h);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    void ImGuiLayer::terminate()
    {
        ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        LOG_INFO("[ImGui] Layer terminating");
    }
} // namespace HYT