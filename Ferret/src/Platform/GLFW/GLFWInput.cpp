#include "Ferret/Core/Input.h"
#include "Ferret/Core/Application.h"

#include "GLFW/glfw3.h"

namespace Ferret
{
    bool Input::IsKeyPressed(KeyCode keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_PRESS;
    }

    bool Input::IsKeyReleased(KeyCode keycode)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
        return state == GLFW_RELEASE;
    }

    bool Input::IsMouseButtonPressed(MouseButton button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonReleased(MouseButton button)
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_RELEASE;
    }

    std::pair<float, float> Input::GetMousePosition()
    {
        auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float Input::GetMouseX()
    {
        auto[x, y] = GetMousePosition();

        return x;
    }

    float Input::GetMouseY()
    {
        auto [x, y] = GetMousePosition();
        return y;
    }
    float Input::GetMouseXOffset()
    {
        float offset = 0;

        if (m_MouseOffsetX == 0)
        {
            m_MouseOffsetX = GetMouseX();
        }
        else if (m_MouseOffsetX != GetMouseX())
        {
            offset = m_MouseOffsetX - GetMouseX();
            m_MouseOffsetX = 0;
        }

        return offset;
    }
    float Input::GetMouseYOffset()
    {
        float offset = 0;

        if (m_MouseOffsetY == 0)
        {
            m_MouseOffsetY = GetMouseY();
        }
        else if (m_MouseOffsetY != GetMouseY())
        {
            offset = m_MouseOffsetY - GetMouseY();
            m_MouseOffsetY = 0;
        }
        return offset;
    }
}
