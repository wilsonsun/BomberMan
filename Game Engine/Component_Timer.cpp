#include "Component_Timer.h"
#include "GameManagers.h"

extern GameManagers *gameManagers;


Component_Timer::Component_Timer():Component(COMPONENT_TIMER)
{
}


Component_Timer::~Component_Timer()
{
}

void Component_Timer::Update()
{
	float frameTime = gameManagers->mpFrameRateController->GetFrameTime() / 1000.0f;
	mTimer -= frameTime;
	if (mTimer < 0)
		mpOwner->mFlag = false;
}

void Component_Timer::Serialize(FILE ** fpp)
{
	fscanf_s(*fpp, "%f\n", &mTimer);
}
