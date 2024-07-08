#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>

class Application
{
public:
    Application();
    ~Application();
    void Run();

private:
    void Initialize();
    void MainLoop();
    void Cleanup();
    static void ErrorCallback(int error, const char* description);

    GLFWwindow* window;
    bool show_demo_window;
    bool show_another_window;
};

#endif // APPLICATION_H
