#pragma once
#include "GameObjectManager.h"
#include "InputManager.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "GameObjectTypeList.h"
#include "EventManager.h"
#include "PhysicsManager.h"
#include "RenderManager.h"
#include <unordered_map>

class GameManagers
{
public:
	GameManagers();
	~GameManagers();

	GameObjectManager		*mpGameObjectManager;
	InputManager			*mpInputManager;
	FrameRateController		*mpFrameRateController;
	ResourceManager			*mpResourceManager;
	SDL_Surface				*pwindowSurface;
	PhysicsManager			*mpPhysicsManager;
	EventManager			*mpEventManager;
	RenderManager			*mpRenderManager;

	std::unordered_map<std::string, GameObjectType> GameObjectMap;
};

