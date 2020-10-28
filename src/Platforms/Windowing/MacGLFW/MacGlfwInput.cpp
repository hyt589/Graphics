#include "MacGlfwInput.hpp"
#include <GLFW/glfw3.h>

namespace HYT
{
    Input *Input::s_Instance = new MacGlfwInput();

    bool MacGlfwInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool MacGlfwInput::IsMouseButtonPressedImpl(int mb)
    {
        auto window = static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow());
        auto state = glfwGetMouseButton(window, mb);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    std::pair<float, float> MacGlfwInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow *>(APP_WINDOW->GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {(float)xpos, (float)ypos};
    }

    float MacGlfwInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float MacGlfwInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }
} // namespace HYT
