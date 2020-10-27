#include "Core.hpp"
#include "SandboxLayer.hpp"
#include "ImGuiLayer.hpp"

using namespace HYT;

int main(int, char **)
{
    auto app = Application::getInstance();
    app->subscribe(EventType::WindowCloseEvent, [app](Event & e)->bool{
        app->setShouldRun(false);
        return true;
    });
    app->pushLayer(new OpenGL::SandboxLayer);
    app->pushOverlay(new ImGuiLayer);
    app->run();
}
