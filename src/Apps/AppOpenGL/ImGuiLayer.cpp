#include "ImGuiLayer.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/string_cast.hpp>
#include <GLFW/glfw3.h>


#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_vulkan.h>

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

        switch (Window::getAPI())
        {
        case WindowAPI::GLFW:
            switch (Graphics::Renderer::getAPI())
            {
            case GraphicsAPI::opengl:
                ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow()), true);
                ImGui_ImplOpenGL3_Init("#version 410");
                break;

            case GraphicsAPI::vulkan:
                // ImGui_ImplGlfw_InitForVulkan(static_cast<GLFWwindow*>(APP_NATIVE_WINDOW), true);
                // ImGui_ImplVulkan_Init()
                LOG_ERROR("Vulkan support not implemented yet");
                exit(1);
                break;

            default:
                LOG_ERROR("GLFW does not support {}", magic_enum::enum_name(Graphics::Renderer::getAPI()));
                exit(1);
                break;
            }
            break;

        default:
            LOG_ERROR("WindowAPI: {}", magic_enum::enum_name(Window::getAPI()));
            exit(1);
            break;
        }
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
        ImGui::Text("%.1f fps", 1.f / seconds);
        ImGui::End();

        end();
    }

    void ImGuiLayer::terminate()
    {
        switch (Graphics::Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            ImGui_ImplOpenGL3_Shutdown();
            break;
        
        default:
            LOG_ERROR("{} is not supported", magic_enum::enum_name(Graphics::Renderer::getAPI()));
            exit(1);
            break;
        }

        switch (Window::getAPI())
        {
        case WindowAPI::GLFW:
            ImGui_ImplGlfw_Shutdown();
            break;

        default:
            LOG_ERROR("WindowAPI: {} is not supported", magic_enum::enum_name(Window::getAPI()));
            exit(1);
            break;
        }

        ImGui::DestroyContext();

        LOG_INFO("[ImGui] Layer terminating");
    }

    void ImGuiLayer::begin()
    {
        switch (Graphics::Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            ImGui_ImplOpenGL3_NewFrame();
            break;

        default:
            LOG_ERROR("Support for {} not implemented", magic_enum::enum_name(Graphics::Renderer::getAPI()));
            exit(1);
            break;
        }

        switch (Window::getAPI())
        {
        case WindowAPI::GLFW:
            ImGui_ImplGlfw_NewFrame();
            break;

        default:
            LOG_ERROR("WindowAPI: {} is not supported", magic_enum::enum_name(Window::getAPI()));
            exit(1);
            break;
        }

        ImGui::NewFrame();
    }

    void ImGuiLayer::end()
    {
        ImGui::Render();
        switch (Graphics::Renderer::getAPI())
        {
        case GraphicsAPI::opengl:
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            break;

        default:
            LOG_ERROR("{} is not supported", magic_enum::enum_name(Graphics::Renderer::getAPI()));
            exit(1);
            break;
        }

        switch (Window::getAPI())
        {
        case WindowAPI::GLFW:
            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow *backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
            break;

        default:
            LOG_ERROR("Unsupported WSI");
            exit(0);
            break;
        }
    }
} // namespace HYT