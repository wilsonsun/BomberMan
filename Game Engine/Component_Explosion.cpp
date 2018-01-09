#include "Component_Explosion.h"
#include "Component_Sprite.h"
#include "GameManagers.h"
#include "Component_BombCollider.h"
#include "Component_Controller.h"
#include "Component_Transform.h"
#include "Component_Body.h"
#include "CollisionEvent.h"
#include "DismissEvent.h"
#include "FireState.h"
#include "GameObjectFactory.h"

extern GameManagers* gameManagers;


Component_Explosion::Component_Explosion() : Component(COMPONENT_EXPLOSION)
{
	mExplosionSize = 1;
	for (int i = 0; i < 4; ++i) 
		mDirFlag[i] = true;
}


Component_Explosion::~Component_Explosion()
{
}

void Component_Explosion::Update()
{
}

void Component_Explosion::Serialize(FILE ** fpp)
{
}

void Component_Explosion::HandleEvent(Event *pEvent)
{
	if (pEvent->eType == EVENT_EXPLODSION) {
		if (pEvent->mpOwner == mpOwner) {

			char imageName[256] = "FireR.png";
			std::string fullPath = "..\\Resources\\";
			fullPath += imageName;
			
			Component_Sprite *pSp = (Component_Sprite*)mpOwner->GetComponent(COMPONENT_SPRITE);
			Component_Body *pBy = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);
			Component_BombCollider *pOwnerBC = (Component_BombCollider*)mpOwner->GetComponent(COMPONENT_BOMBCOLLIDER);
			
			GameObject *pPlacer = pOwnerBC->mpPlacer;
			if (pPlacer->mFlag == true) {
				pPlacer->mNumberofBombs++;
				Component_Body *pPlacerBody = (Component_Body*)pPlacer->GetComponent(COMPONENT_BODY);

				if (pSp != NULL)
					pSp->mTextureID = gameManagers->mpResourceManager->LoadTexture((char*)fullPath.c_str());
				bool r = gameManagers->mpPhysicsManager->mpCollisionMananger->CollisionTest((ShapeAABB*)pBy->mpShape, (ShapeAABB*)pPlacerBody->mpShape);
				if (r) {
					pPlacer->mFlag = false;
					// Game Over Event Here

				}
			}

			// Dismiss mySelf after 2.0 seconds
			Event *timedDismiss = new DismissEvent();
			timedDismiss->mpOwner = mpOwner;
			timedDismiss->mTimer = 0.3f;
			gameManagers->mpEventManager->AddTimedEvent(timedDismiss);
			gameManagers->mpEventManager->Subscribe(EVENT_DISMISS, mpOwner);

			// Player now can move into the bomb
			//Component_BombCollider *pBC = (Component_BombCollider*)mpOwner->GetComponent(COMPONENT_BOMBCOLLIDER);
			if (pPlacer->mFlag == true) {
				Component_Controller *pTr = (Component_Controller*)pOwnerBC->mpPlacer->GetComponent(COMPONENT_CONTROLLER);
				pTr->mbombColliderActive = false;
			}

			// Unsubscribe bomb from EVENT_EXPLOSION 
			gameManagers->mpEventManager->UnSubscribe(EVENT_EXPLODSION, mpOwner);
			
			// Explosion function
			//int size = 2;
			
			bool dirFlag[4];

			for (int j = 0; j < 4; ++j) {
				bool tbool = true;
				for (int i = 0; i < mExplosionSize; ++i) {
					if (!dirFlag[j]) break;
					//if (!tbool) break;

					GameObject *fire = GameObjectFactory::LoadObject("Fire.txt");
					Component_Transform *pOwnerTr = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
					Component_Transform *pFireTr = (Component_Transform*)fire->GetComponent(COMPONENT_TRANSFORM);
					Component_Body *pFireBody = (Component_Body*)fire->GetComponent(COMPONENT_BODY);
					
					if (j == 0)
						fire->mFireState = FIRE_STATE::DIR_RIGHT;
					else if (j == 1)
						fire->mFireState = FIRE_STATE::DIR_LEFT;
					else if (j == 2)
						fire->mFireState = FIRE_STATE::DIR_DOWN;
					else if (j == 3)
						fire->mFireState = FIRE_STATE::DIR_UP;
						
					int sign = j % 2 ? -1 : 1;
					if (j < 2)
					{
						pFireTr->mPosition.x = pOwnerTr->mPosition.x + sign*(i + 1)*50.0f;
						pFireTr->mPosition.y = pOwnerTr->mPosition.y;
					}
					else {
						pFireTr->mPosition.y = pOwnerTr->mPosition.y + sign*(i + 1)*50.0f; 
						pFireTr->mPosition.x = pOwnerTr->mPosition.x;
					}

					pFireBody->Initialize();

					for (int i = 0; i < gameManagers->mpGameObjectManager->gameInstancesList.size(); ++i) {
						GameObject *obj = gameManagers->mpGameObjectManager->gameInstancesList[i];
						if (obj == NULL) continue;
						if (obj->mType == TYPE_FIRE) continue;
						if (obj->mType == TYPE_BOMB) continue;
						Component_Body *pBody = (Component_Body*)obj->GetComponent(COMPONENT_BODY);
						if (pBody == NULL) continue;
						bool r = gameManagers->mpPhysicsManager->mpCollisionMananger->CollisionTest((ShapeAABB*)pFireBody->mpShape, (ShapeAABB*)pBody->mpShape);
						if (r) {
							dirFlag[j] = false;
							
							if (obj->mType == TYPE_MARIO) {
								// Lost condition
								obj->mFlag = false;
								GameObjectFactory::LoadObject("LostUI.txt");
							}
							else if (obj->mType == TYPE_SIMON)
								obj->mFlag = false;
							else if (obj->mType == TYPE_JACK)
								obj->mFlag = false;
							else if (obj->mType == TYPE_WOOD) {
								int iRand = (rand() % 10) + 0;
								if (i % 10 == 0) {
									GameObject *PowerUp = GameObjectFactory::LoadObject("PowerUpFire.txt");
									Component_Transform *pWoodTr = (Component_Transform*)obj->GetComponent(COMPONENT_TRANSFORM);
									Component_Transform *pPUBTr = (Component_Transform*)PowerUp->GetComponent(COMPONENT_TRANSFORM);
									Component_Body *pPUBBy = (Component_Body*)PowerUp->GetComponent(COMPONENT_BODY);
									pPUBTr->mPosition = pWoodTr->mPosition;
									pPUBBy->Initialize();
								}
								else if (i % 10 == 1) {
									GameObject *PowerUp = GameObjectFactory::LoadObject("PowerUpBomb.txt");
									Component_Transform *pWoodTr = (Component_Transform*)obj->GetComponent(COMPONENT_TRANSFORM);
									Component_Transform *pPUBTr = (Component_Transform*)PowerUp->GetComponent(COMPONENT_TRANSFORM);
									Component_Body *pPUBBy = (Component_Body*)PowerUp->GetComponent(COMPONENT_BODY);
									pPUBTr->mPosition = pWoodTr->mPosition;
									pPUBBy->Initialize();
								}
								else if (i % 10 == 2) {
									GameObject *PowerUp = GameObjectFactory::LoadObject("PowerUpSpeed.txt");
									Component_Transform *pWoodTr = (Component_Transform*)obj->GetComponent(COMPONENT_TRANSFORM);
									Component_Transform *pPUBTr = (Component_Transform*)PowerUp->GetComponent(COMPONENT_TRANSFORM);
									Component_Body *pPUBBy = (Component_Body*)PowerUp->GetComponent(COMPONENT_BODY);
									pPUBTr->mPosition = pWoodTr->mPosition;
									pPUBBy->Initialize();
								}
								obj->mFlag = false;
							}
							else
								fire->mFlag = false;
						}
					}

				}
			}
		}		
	}
	else if (pEvent->eType == EVENT_DISMISS) {
		if (pEvent->mpOwner == mpOwner) {
			Component_Sprite *pSp = (Component_Sprite*)mpOwner->GetComponent(COMPONENT_SPRITE);

			if (pSp != NULL)
				pSp->mpSurface = NULL;
		}
		gameManagers->mpEventManager->UnSubscribe(EVENT_DISMISS, mpOwner);
		mpOwner->mFlag = false;
	}
}
