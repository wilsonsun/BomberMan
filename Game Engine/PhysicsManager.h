#pragma once
#include "CollisionManager.h"

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Update();

	CollisionManager *mpCollisionMananger;
};

