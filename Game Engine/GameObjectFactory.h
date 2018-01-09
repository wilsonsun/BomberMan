#pragma once
#include "GameObject.h"
#include "GameObjectTypeList.h"
#include "GameObjectManager.h"
#include "ResourceManager.h"

class GameObjectFactory
{
public:
	static GameObject* CreateGameObectInstance(GameObjectType InstanceType);
	static void LoadLevel(const char *pFileName);
	static GameObject* LoadObject(const char *pFileName);

};

