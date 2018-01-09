#include "GameObjectFactory.h"
#include "GameManagers.h"
#include "Component_Transform.h"
#include "Component_Sprite.h"
#include "Component_Controller.h"
#include "Component_Body.h"
#include "Component_Timer.h"
#include "Component_AI.h"

//#include <vector>

extern GameManagers *gameManagers;

GameObject* GameObjectFactory::CreateGameObectInstance(GameObjectType InstanceType)
{
	GameObject *gameObjectInst = new GameObject();
	gameObjectInst->mType = InstanceType;
	if (InstanceType == TYPE_MARIO)
		gameObjectInst->mNumberofBombs = 1;
	/*
	if (InstanceType == TYPE_MARIO)
		gameObjectInst->mType = TYPE_MARIO;
	else if (InstanceType == TYPE_BEN)
		gameObjectInst->mType = TYPE_BEN;
	else if (InstanceType == TYPE_JACK)
		gameObjectInst->mType = TYPE_JACK;
	else if (InstanceType == TYPE_SIMON)
		gameObjectInst->mType = TYPE_SIMON;
	else if (InstanceType == TYPE_BOMB)
		gameObjectInst->mType = TYPE_BOMB;
	else if (InstanceType == TYPE_FIRE)
		gameObjectInst->mType = TYPE_FIRE;
		*/

	gameObjectInst->mIsMoving = false;
	gameObjectInst->mState = Down;

	// Add this newly created game object to the gameObjectList
	std::vector<GameObject*> &GIList = gameManagers->mpGameObjectManager->gameInstancesList;
	for (int i = 0; i < GIList.size(); ++i) {
		if (GIList[i] == NULL) {
			GIList[i] = gameObjectInst;
			return gameObjectInst;
		}
	}
	// Otherwise add it to the tail
	gameManagers->mpGameObjectManager->gameInstancesList.push_back(gameObjectInst);
	return gameObjectInst;
}

void GameObjectFactory::LoadLevel(const char * pFileName)
{
	FILE *fp;
	fopen_s(&fp, pFileName, "r");

	if (fp) {
		while (!feof(fp)) {
			char objectFileName[256];
			memset(objectFileName, 0, 256 * sizeof(char));
			fscanf_s(fp, "%255s", objectFileName, sizeof(objectFileName));

			//std::string fullPath = "..\\Resources\\";
			//fullPath += objectFileName;

			GameObject *pNewObject = LoadObject(objectFileName);

			Component_Transform *pTr = (Component_Transform *)pNewObject->GetComponent(COMPONENT_TRANSFORM);
			pTr->Serialize(&fp);

			// Set Body Component mPos to Transform Component mPos
			Component_Body *pBody = (Component_Body *)pNewObject->GetComponent(COMPONENT_BODY);
			if (pBody != NULL)
				pBody->Initialize();
		}
		fclose(fp);
	}
}

GameObject * GameObjectFactory::LoadObject(const char * pFileName)
{
	GameObject *pNewObject = NULL;

	FILE *fp;
	fopen_s(&fp, pFileName, "r");

	if (fp) {
		char playerType[256];
		fscanf_s(fp, "%255s", playerType, sizeof(playerType));

		GameObjectType gOt = gameManagers->GameObjectMap[playerType];
		pNewObject = GameObjectFactory::CreateGameObectInstance(gOt);

		if (pNewObject == NULL) {
			printf("CANNOT LOAD GAME OBJECT\n");
			return NULL;
		}

		while (!feof(fp)) {
			char componentType[256];
			memset(componentType, 0, 256 * sizeof(char));

			fscanf_s(fp, "%255s", componentType, sizeof(componentType));

			if (strcmp(componentType, "Transform") == 0) {
				pNewObject->AddComponent_Transform();
				Component_Transform *pTr = (Component_Transform *)pNewObject->GetComponent(COMPONENT_TRANSFORM);
				pTr->Serialize(&fp);
			}
			else if (strcmp(componentType, "Sprite") == 0) {
				pNewObject->AddComponent_Sprite();
				Component_Sprite *pSp = (Component_Sprite*)pNewObject->GetComponent(COMPONENT_SPRITE);
				pSp->Serialize(&fp);
			}
			else if (strcmp(componentType, "Controller") == 0) {
				pNewObject->AddComponent_Controller();
				Component_Controller *pCn = (Component_Controller*)pNewObject->GetComponent(COMPONENT_CONTROLLER);
				pCn->Serialize(&fp);
			}
			else if (strcmp(componentType, "UpDown") == 0) {
				pNewObject->AddComponent_UpDown();
			}
			else if (strcmp(componentType, "AI") == 0) {
				pNewObject->AddComponent_AI();
			}
			else if (strcmp(componentType, "Animation") == 0) {
				pNewObject->AddComponent_Animation();
			}
			else if (strcmp(componentType, "Body") == 0) {
				pNewObject->AddComponent_Body();
				Component_Body *pBody = (Component_Body*)pNewObject->GetComponent(COMPONENT_BODY);
				pBody->Serialize(&fp);
			}
			else if (strcmp(componentType, "Explosion") == 0) {
				pNewObject->AddComponent_Explosion();
			}
			else if (strcmp(componentType, "BombCollider") == 0) {
				pNewObject->AddComponent_BombCollider();
			}
			else if (strcmp(componentType, "Timer") == 0) {
				pNewObject->AddComponent_Timer();
				Component_Timer *pTimer = (Component_Timer*)pNewObject->GetComponent(COMPONENT_TIMER);
				pTimer->Serialize(&fp);
			}
		}

		fclose(fp);
	}

	return pNewObject;
}


