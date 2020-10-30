#include "Core.hpp"
#include "SandboxLayer.hpp"
#include "ImGuiLayer.hpp"

using namespace HYT;

int main(int, char **)
{
    Graphics::Renderer::setAPI(GraphicsAPI::opengl);
    Window::setAPI(WindowAPI::GLFW);
    auto app = Application::getInstance(
        "wtf",
        1280u, 720u,
        4, 1);
    app->subscribe(EventType::WindowCloseEvent, [app](Event &e) -> bool {
        app->setShouldRun(false);
        return true;
    });
    app->pushLayer(new OpenGL::SandboxLayer);
    app->pushOverlay(new ImGuiLayer);
    app->run();
}
