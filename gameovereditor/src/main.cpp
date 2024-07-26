#include <iostream>
#include "gameover/engine.h"

int main() {
    gameover::Engine& engine = gameover::Engine::Instance();
    if(engine.Initialize())
    {

        while(true)
        {
            // Game loop
        }
    }
    engine.Shutdown();
    return 0;
}