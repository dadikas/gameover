#ifdef APPLICATION_HPP
#define APPLICATION_HPP

#include <GLFW/glfw3.h>

class Application
{
public:
    Application();
    ~Application();
    void run();
private:
    GLFWwindow* window;
    void init();
    void loop();
    void cleanup();
};
#endif // APPLICATION_HPP