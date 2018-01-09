#pragma once
#include "Component.h"

class Component_Explosion : public Component
{
public:
	Component_Explosion();
	~Component_Explosion();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent);
	volatile bool mDirFlag[4];
	int mExplosionSize;
};

