#pragma once
#include <vector>
#include <list>
#include "GameObject.h"
#include <SDL.h>

class GameObjectManager
{
public:
	std::vector<GameObject *> gameInstancesList;

	GameObjectManager();
	~GameObjectManager();

	void Update();
};

