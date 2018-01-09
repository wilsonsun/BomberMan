#pragma once
#include "Component.h"
class Component_Timer : public Component
{
public:
	Component_Timer();
	~Component_Timer();

	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent) {}
private:
	float mTimer;
};

