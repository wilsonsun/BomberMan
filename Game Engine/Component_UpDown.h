#pragma once
#include "Component.h"

class Component_UpDown : public Component
{
public:
	Component_UpDown();
	~Component_UpDown();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent);

	bool mGoingUp;
	unsigned int mTimer;
	bool mLockUp;
	bool mLockDown;
};

