#pragma once
#include "Event.h"
#include "GameObject.h"
#include <list>

class CollisionEvent : public Event
{
public:
	CollisionEvent();
	~CollisionEvent();

	std::vector<GameObject*> mpObjects;

};

