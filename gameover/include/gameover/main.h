#pragma once

#include "gameover/engine.h"
#include "gameover/app.h"

gameover::App* CreateApp();

int main() {
	gameover::App* app = CreateApp();
	gameover::Engine::Instance().Run(app);
	delete app;
	return 0;
}