#include "gameover/input/mouse.h"
#include"gameover/log.h"

#include <algorithm>


#include <sdl2/SDL_mouse.h>

namespace gameover::input {
	int Mouse::x = 0;
	int Mouse::xlast = 0;
	int Mouse::y = 0;
	int Mouse::ylast = 0;

	std::array<bool, Mouse::ButtonCount> Mouse::buttons;
	std::array<bool, Mouse::ButtonCount> Mouse::buttonslast;

	void Mouse::Initialize() {
		std::fill(buttons.begin(), buttons.end(), false);
		std::fill(buttonslast.begin(), buttonslast.end(), false);
	}

	void Mouse::Update() {
		xlast = x;
		ylast = y;

		buttonslast = buttons;

		Uint32 state = SDL_GetMouseState(&x, &y);
		for (int i = 0; i < ButtonCount; ++i) {
			buttons[i] = state & SDL_BUTTON(i + 1);
		}
	}

	bool Mouse::Button(int button)
	{
		GAMEOVER_ASSERT(button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST, "Invalid mouse button!");
		if (button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST)
		{
			return buttons[button - 1];
		}
		return false;
	}

	bool Mouse::ButtonDown(int button)
	{
		GAMEOVER_ASSERT(button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST, "Invalid mouse button!");
		if (button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST)
		{
			return buttons[button - 1] && buttonslast[button - 1];
		}
		return false;
	}

	bool Mouse::ButtonUp(int button)
	{
		GAMEOVER_ASSERT(button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST, "Invalid mouse button!");
		if (button >= GAMEOVER_INPUT_MOUSE_FIRST && button <= GAMEOVER_INPUT_MOUSE_LAST)
		{
			return !buttons[button - 1] && buttonslast[button - 1];
		}
		return false;
	}
}

