#include "FrameRateController.h"
#include "limits.h"
#include "SDL_timer.h"
#include <stdio.h>


FrameRateController::FrameRateController(unsigned int MaxFrameRate)
{
	if (MaxFrameRate == 0)
		MaxFrameRate = UINT_MAX;
	
	mMaxFrameRate = MaxFrameRate;
	mTicksPerFrame = 1000 / mMaxFrameRate;
	mTickStart = 0;
	mTickEnd = 0;
}


FrameRateController::~FrameRateController()
{
}

void FrameRateController::FrameStart(void)
{
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd(void)
{
	mTickEnd = SDL_GetTicks();

	while ((mTickEnd - mTickStart) < mTicksPerFrame)
		mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
}

unsigned int FrameRateController::GetFrameTime(void)
{
	return mFrameTime;
}
