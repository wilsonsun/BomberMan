#pragma once

#include "SDL_stdinc.h"

class InputManager
{
public:
	InputManager();
	~InputManager();
	void Update();
	bool IsKeyPressed(unsigned int KeyScanCode);
	bool IsKeyTriggered(unsigned int KeyScanCode);
	bool IsKeyRelease(unsigned int KeyScanCode);
private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
};

