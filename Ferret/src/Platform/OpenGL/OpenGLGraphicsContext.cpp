#include "fepch.h"
#include "OpenGLGraphicsContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Ferret
{
    OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
    : m_Window(windowHandle)
    {
        FE_API_ASSERT(windowHandle, "Window Handle is null!");
    }

    void OpenGLGraphicsContext::Init()
    {
        glfwMakeContextCurrent(m_Window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        FE_API_ASSERT(status, "Failed to load GLAD");

        #ifdef CE_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        CE_API_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "CatEngine requires at least OpenGL version 4.5!");
        #endif
    }

    void OpenGLGraphicsContext::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }
}
