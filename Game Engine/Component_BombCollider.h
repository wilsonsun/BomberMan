#pragma once
#include "Component.h"

class Component_BombCollider : public Component
{
public:
	Component_BombCollider();
	~Component_BombCollider();
	void Update();
	void Serialize(FILE **fpp) {};
	void HandleEvent(Event *pEvent) {}
	
	GameObject *mpPlacer;
	bool mActiveFLAG;
	float mClock;
};

