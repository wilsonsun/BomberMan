#include "GameObjectManager.h"
#include "Component_Body.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (int i = 0; i < gameInstancesList.size(); ++i) {
		if (gameInstancesList[i] == NULL) continue;
		delete gameInstancesList[i];
	}
	gameInstancesList.clear();
}

void GameObjectManager::Update()
{
	for (int i = 0; i < gameInstancesList.size(); ++i) {
		//GameObject *obj = gameInstancesList[i];
		if (gameInstancesList[i] == NULL) continue;

		if (gameInstancesList[i]->mFlag == false) {
			delete gameInstancesList[i];
			gameInstancesList[i] = NULL;
			continue;
		} 
		gameInstancesList[i]->Update();
	}
}


