#include "Component_AI.h"
#include "GameManagers.h"
#include "Component_Transform.h"
#include "CollisionEvent.h"

#define SPEED 5.0

extern GameManagers *gameManagers;


Component_AI::Component_AI():Component(COMPONENT_AI), mDir(-1), mLock(-1)
{
}


Component_AI::~Component_AI()
{
}

void Component_AI::Update()
{
	mTimer += gameManagers->mpFrameRateController->GetFrameTime();
	if (mTimer > 1000) {
		//mGoingUp = !mGoingUp;
		//Generate Random Number here for the direction that the char is moving to
		int iRand = (rand() % 10) + 0;

		mDir = iRand % 4;

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
	if (mDir == 0 && mLock != 0) {
		mLock = -1;
		//mLockDown = true;
		mpOwner->mState = PlayerState::Up;
		pTr->mPosition.y -= SPEED;
		//pBy->mVelocity.y -= SPEED;
	}
	if (mDir == 1 && mLock != 1) {
		mLock = -1;
		mpOwner->mState = PlayerState::Down;
		pTr->mPosition.y += SPEED;
		//pBy->mVelocity.y += SPEED;
	}
	if (mDir == 2 && mLock != 2) {
		mLock = -1;
		mpOwner->mState = PlayerState::Left;
		pTr->mPosition.x -= SPEED;
		//pBy->mVelocity.y += SPEED;
	}
	if (mDir == 3 && mLock != 3) {
		mLock = -1;
		mpOwner->mState = PlayerState::Right;
		pTr->mPosition.x += SPEED;
		//pBy->mVelocity.y += SPEED;
	}
	pBy->Initialize();

}

void Component_AI::Serialize(FILE ** fpp)
{
}

void Component_AI::HandleEvent(Event * pEvent)
{
	
	if (pEvent->eType == EVENT_COLLISION) {
		CollisionEvent *collisionEvent = (CollisionEvent*)pEvent;
		GameObject *obj1 = collisionEvent->mpObjects[0];
		GameObject *obj2 = collisionEvent->mpObjects[1];

		// Swap it if needed...
		if (obj2->mType == TYPE_JACK) {
			GameObject *temp = obj1;
			obj1 = obj2;
			obj2 = temp;
		}

		if (obj1->mType == TYPE_JACK && obj2->mType != TYPE_MARIO) {
			mLock = mDir;

			// Position Adjustment
			Component_Body *pBody = (Component_Body*)obj1->GetComponent(COMPONENT_BODY);

			pBody->mVelocity.x = 0.0f;
			pBody->mVelocity.y = 0.0f;

			Component_Transform *pTr = (Component_Transform*)obj1->GetComponent(COMPONENT_TRANSFORM);

			if (mDir == 0) {
				pTr->mPosition.y = pBody->mPrevPosition.y + 5;
			}
			else if (mDir == 1) {
				pTr->mPosition.y = pBody->mPrevPosition.y - 5;
			}
			else if (mDir == 2) {
				pTr->mPosition.x = pBody->mPrevPosition.x + 5;
			}
			else if (mDir == 3) {
				pTr->mPosition.x = pBody->mPrevPosition.x - 5;
			}
		}

		Component_Body *componentBody = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);

		if (componentBody != NULL) {
			componentBody->Initialize();
		}

	}
	
}
