#include "Core.hpp"
#include "SandboxLayer.hpp"
#include "ImGuiLayer.hpp"

using namespace HYT;

int main(int, char **)
{
    auto app = Application::getInstance(
        "GL 4.1 sandbox", 
        1280u, 720u, 
        4, 1
    );
    app->subscribe(EventType::WindowCloseEvent, [app](Event & e)->bool{
        app->setShouldRun(false);
        return true;
    });
    app->pushLayer(new OpenGL::SandboxLayer);
    app->pushOverlay(new ImGuiLayer);
    app->run();
}
