#include "Core.hpp"

using namespace HYT;

int main(int, char **)
{
    auto app = Application::getInstance();
    app->subscribe(EventType::WindowCloseEvent, [app](Event & e)->bool{
        app->shouldRun(false);
        return true;
    });
    app->run();
}
