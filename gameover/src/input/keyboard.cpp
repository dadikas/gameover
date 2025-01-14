#include "gameover/input/keyboard.h"
#include "gameover/log.h"

#include <algorithm>

#include "sdl2/SDL_keyboard.h"

namespace gameover::input{

	std::array<bool, Keyboard::KeyCount> Keyboard::keys;
	std::array<bool, Keyboard::KeyCount> Keyboard::keysLast;

	void Keyboard::Initialize()
	{
		std::fill(keys.begin(), keys.end(), false);
		std::fill(keysLast.begin(), keysLast.end(), false);
	}

	void Keyboard::Update()
	{
		keysLast = keys;
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		for (int i = GAMEOVER_INPUT_KEY_FIRST; i < KeyCount; i++)
		{
			keys[i] = state[i];
		}
	}

	bool Keyboard::Key(int key)
	{
		GAMEOVER_ASSERT(key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount, "Invalid keyboard key!");
		if (key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount)
		{
			return keys[key];
		}
		return false;
	}

	bool Keyboard::KeyDown(int key)
	{
		GAMEOVER_ASSERT(key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount, "Invalid keyboard key!");
		if (key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount)
		{
			return keys[key] && !keysLast[key];
		}
		return false;
	}

	bool Keyboard::KeyUp(int key)
	{
		GAMEOVER_ASSERT(key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount, "Invalid keyboard key!");
		if (key >= GAMEOVER_INPUT_KEY_FIRST && key < KeyCount)
		{
			return !keys[key] && keysLast[key];
		}
		return false;
	}
}