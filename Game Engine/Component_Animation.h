#pragma once
#include "Component.h"
class Component_Animation : public Component
{
public:
	Component_Animation();
	~Component_Animation();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent);
private:
	int mTimer;
};

