#include "application.h"
#include <iostream>
int main()
{
    try
    {
        Application app;
        app.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}