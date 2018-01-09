#include "InputManager.h"
#include "SDL_config.h"
#include "memory.h"
#include "SDL_keyboard.h"


InputManager::InputManager()
{
	memset(mCurrentState, 0, 512*sizeof(Uint8));
}


InputManager::~InputManager()
{
}

void InputManager::Update()
{
	int fetchedNum = 0;
	const Uint8 *currentKeyStates = SDL_GetKeyboardState(&fetchedNum);

	if (fetchedNum > 512) { fetchedNum = 512; }

	// Copy current to previous
	memcpy(mPreviousState, mCurrentState, fetchedNum * sizeof(Uint8));
	// Fill current with new inputs
	memcpy(mCurrentState, currentKeyStates, fetchedNum*sizeof(Uint8));
}

bool InputManager::IsKeyPressed(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;

	return false;
}

bool InputManager::IsKeyTriggered(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512)
		return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
		return true;

	return false;
}

bool InputManager::IsKeyRelease(unsigned int KeyScanCode)
{
	if (KeyScanCode > 512)
		return false;

	if (!mCurrentState[KeyScanCode] && mPreviousState[KeyScanCode])
		return true;

	return false;
}
