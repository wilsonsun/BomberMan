#include "Component_UpDown.h"
#include "Component_Transform.h"
#include "GameObject.h"
#include "GameManagers.h"
#include "PlayerState.h"
#include "Component_Body.h"
#include "CollisionEvent.h"
#include "GameObjectFactory.h"

#define SPEED 1.0

extern GameManagers *gameManagers;

Component_UpDown::Component_UpDown() : Component(COMPONENT_UPDOWN)
{
	mpOwner = NULL;
	mGoingUp = true;
	mTimer = 0;
	mLockDown = true;
	mLockUp = true;
}

Component_UpDown::~Component_UpDown()
{
}

void Component_UpDown::Update()
{
	mTimer += gameManagers->mpFrameRateController->GetFrameTime();
	if (mTimer > 3000) {
		mGoingUp = !mGoingUp;
		mTimer = 0;
	}

	Component_Transform *pTr = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	if (pTr == NULL) {
		printf("Component_Update cannot find Component_Transform\n");
		return;
	}

	Component_Body *pBy = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);
	if (pBy == NULL) {
		return;
	}

	mpOwner->mIsMoving = true;
	if (mGoingUp && mLockUp) {
		mLockDown = true;
		mpOwner->mState = PlayerState::Up;
		pTr->mPosition.y -= 5.0f;
		//pBy->mVelocity.y -= SPEED;
	}
	if (!mGoingUp && mLockDown) {
		mLockUp = true;
		mpOwner->mState = PlayerState::Down;
		pTr->mPosition.y += 5.0f;
		//pBy->mVelocity.y += SPEED;
	}
	pBy->Initialize();
}

void Component_UpDown::Serialize(FILE ** fpp)
{
}

void Component_UpDown::HandleEvent(Event * pEvent)
{
	if (pEvent->eType == EVENT_COLLISION) {
		CollisionEvent *collisionEvent = (CollisionEvent*)pEvent;
		GameObject *obj1 = collisionEvent->mpObjects[0];
		GameObject *obj2 = collisionEvent->mpObjects[1];

		// Swap it if needed...
		if (obj2->mType == TYPE_SIMON) {
			GameObject *temp = obj1;
			obj1 = obj2;
			obj2 = temp;
		}

		if (obj1->mType == TYPE_SIMON && obj2->mType != TYPE_MARIO) {
			if (mGoingUp)
				mLockUp = false;
			else
				mLockDown = false;
		}
		/*
		if (obj1->mType == TYPE_SIMON && obj2->mType == TYPE_MARIO) {
			GameObjectFactory::LoadObject("LoseUI.txt");
		}
		*/
	}
	
}
