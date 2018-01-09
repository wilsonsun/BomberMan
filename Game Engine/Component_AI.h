#pragma once
#include "Component.h"

class Component_AI : public Component
{
public:
	Component_AI();
	~Component_AI();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent);

	unsigned int mTimer;
	int mDir;
	int mLock;
};

