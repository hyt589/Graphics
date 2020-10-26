#include "Core.hpp"
#include "SandboxLayer.hpp"

using namespace HYT;

int main(int, char **)
{
    auto app = Application::getInstance();
    app->subscribe(EventType::WindowCloseEvent, [app](Event & e)->bool{
        app->setShouldRun(false);
        return true;
    });
    app->pushLayer(new OpenGL::SandboxLayer);
    app->run();
}
