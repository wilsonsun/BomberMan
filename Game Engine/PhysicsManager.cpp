#include "PhysicsManager.h"
#include "Component_Body.h"
#include "GameManagers.h"
#include "CollisionEvent.h"

extern GameManagers *gameManagers;

PhysicsManager::PhysicsManager()
{
	mpCollisionMananger = new CollisionManager();
}

PhysicsManager::~PhysicsManager()
{
	delete mpCollisionMananger;
}

void PhysicsManager::Update()
{
	for (auto object : gameManagers->mpGameObjectManager->gameInstancesList) {
		if (object == NULL) continue;
		Component_Body *pBody = (Component_Body*)object->GetComponent(COMPONENT_BODY);
		if (pBody != NULL) {
			pBody->Integrate(gameManagers->mpFrameRateController->GetFrameTime()/1000.0f);
		}
	}

	mpCollisionMananger->Reset();

	unsigned int index1, index2, gameObjectNum = gameManagers->mpGameObjectManager->gameInstancesList.size();

	for (index1 = 0; index1 < gameObjectNum; ++index1) {
		if (gameManagers->mpGameObjectManager->gameInstancesList[index1] == NULL) continue;
		Component_Body *pBody1 = (Component_Body*)(gameManagers->mpGameObjectManager->gameInstancesList[index1]->GetComponent(COMPONENT_BODY));
		if (pBody1 == NULL) continue;
		
		for (index2 = index1 + 1; index2 < gameObjectNum; ++index2) {
			if (gameManagers->mpGameObjectManager->gameInstancesList[index2] == NULL) continue;
			Component_Body *pBody2 = (Component_Body*)(gameManagers->mpGameObjectManager->gameInstancesList[index2]->GetComponent(COMPONENT_BODY));
			if (pBody2 == NULL) continue;
			mpCollisionMananger->CollisionTest((ShapeAABB*)pBody1->mpShape, (ShapeAABB*)pBody2->mpShape);

			// Broadcast the event here if no one collides with the bomb
		}
	}

	// Resolve Collision Here
	for (auto c : mpCollisionMananger->mContacts) {
		CollisionEvent collisionEvent;
		collisionEvent.mpObjects.push_back(c->mpBodies[0]->mpOwner);
		collisionEvent.mpObjects.push_back(c->mpBodies[1]->mpOwner);

		c->mpBodies[0]->mpOwner->HandleEvent(&collisionEvent);
		c->mpBodies[1]->mpOwner->HandleEvent(&collisionEvent);
	}

	//printf("%d\n",mpCollisionMananger->mContacts.size());
}
