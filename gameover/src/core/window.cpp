#include "gameover/core/window.h"  // Include header file of Window class
#include "gameover/graphics/framebuffer.h"
namespace gameover::core
{
    bool Window::Create(const WindowProperties& props)
    {
        return true;
    }

    void Window::Shutdown()
    {
    }

    void Window::PumpEvents()
    {
    }

    glm::ivec2 Window::GetSize() {
        return glm::ivec2(0,0);
    }

    void Window::BeginRender()
    {
    }

    void Window::EndRender()
    {
    }

}
