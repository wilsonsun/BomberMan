#pragma once
#include "ComponentList.h"
#include <iostream>
#include "Event.h"

class GameObject;

class Component
{
public:
	Component(ComponentType Type);
	virtual ~Component();

	virtual void Update() = 0;
	virtual void Serialize(FILE **fpp) = 0;
	virtual void HandleEvent(Event *pEvent) {}

	GameObject *mpOwner;
	ComponentType mType;

};

