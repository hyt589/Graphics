#include "input.hpp"
#include "MacGlfw.hpp"

namespace HYT
{
    Input *Input::s_Instance;

    void Input::init()
    {
        switch (Window::getAPI())
        {
        case WindowAPI::GLFW:
        {

#ifdef HYT_PLATFORM_MAC_OS
            s_Instance = new MacGlfwInput();
#endif // HYT_PLATFORM_MAC_OS

            break;
        }
        default:
        {
            LOG_ERROR("Fatal error: Window API: {} not supported", std::string(magic_enum::enum_name(Window::getAPI())));
            exit(1);
            break;
        }
        }
    }
} // namespace HYT
