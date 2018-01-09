#include "Component_Controller.h"
#include "ComponentList.h"
#include "Component_Transform.h"
#include "Component_Body.h"
#include "Component_Sprite.h"
#include "Component_BombCollider.h"
#include "Component_Explosion.h"
#include "CollisionEvent.h"
#include "GameObjectFactory.h"
#include "GameManagers.h"
#include "ExplosionEvent.h"
//#define SPEED 200.0;

extern GameManagers *gameManagers;

Component_Controller::Component_Controller() : Component(COMPONENT_CONTROLLER)
{
	mbombColliderActive = true;
	EnableControls();
	mInCurBomb = false;
	SPEED = 200.0;
	EXPLOSIONLENGTH = 1;
}

Component_Controller::~Component_Controller()
{
}

void Component_Controller::Update()
{
	Component_Transform *componentTransform = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	if (componentTransform == NULL)
		return;
		
	Component_Body *pBody = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);
	if (pBody == NULL)
		return;
	
	if (mpinputManager->IsKeyTriggered(SDL_SCANCODE_SPACE) && mpOwner->mNumberofBombs > 0) {
		mpOwner->mNumberofBombs--;

		if (mInCurBomb == true)
			return;
		mInCurBomb = true;
		//if (mpOwner->mNumberofBombs != 0) return;
		// Generate Bomb and initialize its position 
		GameObject *bomb = GameObjectFactory::LoadObject("Bomb.txt");
		// Set LastBomb and BombCollider State
		//if (mpLastBomb == NULL)
		mpLastBomb = bomb;
		mbombColliderActive = false;

		// Setting BombCollider's placer
		Component_BombCollider *pBombCd = (Component_BombCollider*)bomb->GetComponent(COMPONENT_BOMBCOLLIDER);
		if (pBombCd != NULL) {
			pBombCd->mpPlacer = mpOwner;
		}
		// Setting Explosion's Length
		Component_Explosion *pEx = (Component_Explosion*)bomb->GetComponent(COMPONENT_EXPLOSION);
		if (pEx != NULL) {
			pEx->mExplosionSize = EXPLOSIONLENGTH;
		}

		// Sync its Transform Position 
		Component_Transform *pBombTr = (Component_Transform*)bomb->GetComponent(COMPONENT_TRANSFORM);
		Component_Transform *pOwnerTr = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);

		if (pBombTr != NULL && pOwnerTr != NULL) {
			pBombTr->mPosition.x = pOwnerTr->mPosition.x;
			pBombTr->mPosition.y = pOwnerTr->mPosition.y;

			if (pBombTr->mPosition.x < 70.0f)
				pBombTr->mPosition.x = 70.0f;
			/*
			else if (((int)pBombTr->mPosition.x - 70) % 60 >= 30) {
				int delta = 60-((int)pBombTr->mPosition.x - 70) % 60;
				pBombTr->mPosition.x -= delta;
			}
			else {
				int delta = ((int)pBombTr->mPosition.x - 70) % 60;
				pBombTr->mPosition.x += delta;
			}
			*/
		}

		// Initialize his Body Component
		Component_Body *pBody = (Component_Body*)bomb->GetComponent(COMPONENT_BODY);

		if (pBody != NULL) {
			pBody->Initialize();
		}

		// Add Timed Event
		Event *timedExplosion = new ExplosionEvent();
		timedExplosion->mpOwner = bomb;
		timedExplosion->mTimer = 2.0f;
		gameManagers->mpEventManager->AddTimedEvent(timedExplosion);
		gameManagers->mpEventManager->Subscribe(EVENT_EXPLODSION, bomb);
		
	}

	if (mpinputManager->IsKeyPressed(SDL_SCANCODE_UP)) {
		if (!mControllerSwitches[Up]) return;
		EnableControls();
		//componentTransform->mPosition.y -= 1;
		pBody->mVelocity.y = -SPEED;
		pBody->mVelocity.x = 0.0f;
		//posY -= 1;
		mpOwner->mState = Up;
		mpOwner->mIsMoving = true;
	}
	else if (mpinputManager->IsKeyPressed(SDL_SCANCODE_DOWN)) {
		if (!mControllerSwitches[Down]) return;
		EnableControls();
		//componentTransform->mPosition.y += 1;
		pBody->mVelocity.y = SPEED;
		pBody->mVelocity.x = 0.0f;
		//posY += 1;
		mpOwner->mState = Down;
		mpOwner->mIsMoving = true;
	}
	else if (mpinputManager->IsKeyPressed(SDL_SCANCODE_LEFT)) {
		if (!mControllerSwitches[Left]) return;
		EnableControls();
		//componentTransform->mPosition.x -= 1;
		pBody->mVelocity.x = -SPEED;
		pBody->mVelocity.y = 0.0f;
		//posX -= 1;
		mpOwner->mState = Left;
		mpOwner->mIsMoving = true;
	}
	else if (mpinputManager->IsKeyPressed(SDL_SCANCODE_RIGHT)) {
		if (!mControllerSwitches[Right]) return;
		EnableControls();
		//componentTransform->mPosition.x += 1;
		pBody->mVelocity.x = SPEED;
		pBody->mVelocity.y = 0.0f;
		//posX += 1;
		mpOwner->mState = Right;
		mpOwner->mIsMoving = true;
	}
	else {
		// Otherwise, player is not moving
		mpOwner->mIsMoving = false;
		pBody->mVelocity.x = 0.0f;
		pBody->mVelocity.y = 0.0f;
	}
}

void Component_Controller::Serialize(FILE **fpp)
{
}

void Component_Controller::HandleEvent(Event * pEvent)
{
	GameObject *tObj;
	if (pEvent->eType == EVENT_COLLISION) {
		
		CollisionEvent *collisionEvent = (CollisionEvent*)pEvent;
		GameObject *obj1 = collisionEvent->mpObjects[0];
		GameObject *obj2 = collisionEvent->mpObjects[1];

		// Swap it if needed...
		if (obj2->mType == TYPE_MARIO) {
			GameObject *temp = obj1;
			obj1 = obj2;
			obj2 = temp;
		}

		if (obj1->mType == TYPE_MARIO) {
			if (obj2 == mpLastBomb && mbombColliderActive == false)
				return;
				
			// When you hit the fire, die...
			if (obj2->mType == TYPE_SIMON || obj2->mType == TYPE_JACK) {
				obj1->mFlag = false;
				GameObjectFactory::LoadObject("LostUI.txt");
				return;
			}
			else if (obj2->mType == TYPE_POWERUP_BOMB) {
				obj1->mNumberofBombs++;
				obj2->mFlag = false;
			}
			else if (obj2->mType == TYPE_POWERUP_FIRE) {
				EXPLOSIONLENGTH++;
				obj2->mFlag = false;
			}
			else if (obj2->mType == TYPE_POWERUP_SPEED) {
				SPEED += 50.0;
				obj2->mFlag = false;
			}
			else if (obj2->mType == TYPE_DOOR) {
				// Winning Condition!
				obj1->mFlag = false;
				GameObjectFactory::LoadObject("WinUI.txt");

			}

			obj1->mIsMoving = false;
			Component_Body *pBody = (Component_Body*)obj1->GetComponent(COMPONENT_BODY);
			
			pBody->mVelocity.x = 0.0f;
			pBody->mVelocity.y = 0.0f;

			Component_Transform *pTr = (Component_Transform*)obj1->GetComponent(COMPONENT_TRANSFORM);

			// Position Adjustment
			if (obj2->mType != TYPE_POWERUP_BOMB && obj2->mType != TYPE_POWERUP_FIRE && obj2->mType != TYPE_POWERUP_SPEED && obj2->mType != TYPE_DOOR) {
				if (obj1->mState == Right) {
					pTr->mPosition.x = pBody->mPrevPosition.x - 0.1f;
					mControllerSwitches[Right] = false;
				}
				else if (obj1->mState == Left) {
					pTr->mPosition.x = pBody->mPrevPosition.x + 0.1f;
					mControllerSwitches[Left] = false;
				}
				else if (obj1->mState == Up) {
					pTr->mPosition.y = pBody->mPrevPosition.y + 0.1f;
					mControllerSwitches[Up] = false;
				}
				else if (obj1->mState == Down) {
					pTr->mPosition.y = pBody->mPrevPosition.y - 0.1f;
					mControllerSwitches[Down] = false;
				}
			}
		}
		Component_Body *componentBody = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);

		if (componentBody != NULL) {
			componentBody->Initialize();
		}
	}
}

void Component_Controller::EnableControls()
{
	for (int i = 0; i < 4; ++i) {
		mControllerSwitches[i] = true;
	}
}

