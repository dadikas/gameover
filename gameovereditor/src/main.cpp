#include <iostream>
#include "gameover/engine.h"

int main() {
    gameover::Engine& engine = gameover::Engine::Instance();
    engine.Run();
    return 0;
}