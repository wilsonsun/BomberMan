#include "Component_Body.h"
#include "Component_Transform.h"
#include "Component_BombCollider.h"
#include "CollisionEvent.h"
#include "GameObject.h"
#include "Shape.h"

Component_Body::Component_Body():Component(COMPONENT_BODY)
{
	mPrevPosition.x = 0.0f;
	mPrevPosition.y = 0.0f;
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mVelocity.x = 0.0f;
	mVelocity.y = 0.0f;

	mpShape = NULL;
}


Component_Body::~Component_Body()
{

}

void Component_Body::Update()
{
}

void Component_Body::Serialize(FILE ** fpp)
{
	char shapeType[256];
	memset(shapeType, 0, sizeof(shapeType));
	fscanf_s(*fpp, "%255s\n", shapeType, sizeof(shapeType));

	if (strcmp(shapeType, "AABB") == 0) {
		mpShape = new ShapeAABB();
		mpShape->mpOwnerBody = this;

		ShapeAABB *pAABB = (ShapeAABB*)mpShape;
		fscanf_s(*fpp, "%f %f\n", &pAABB->mWidth, &pAABB->mHeight);
	}
}

void Component_Body::Initialize()
{
	Component_Transform *componentTransform = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);

	if (componentTransform != NULL) {
		mPosition.x = componentTransform->mPosition.x;
		mPosition.y = componentTransform->mPosition.y;
	}
}

void Component_Body::Integrate(float dt)
{
	mPrevPosition.x = mPosition.x;
	mPrevPosition.y = mPosition.y;

	//Initialize();

	mPosition.x = mVelocity.x * dt + mPosition.x;
	mPosition.y = mVelocity.y * dt + mPosition.y;

	Component_Transform *componentTransform = (Component_Transform*)mpOwner->GetComponent(COMPONENT_TRANSFORM);
	
	if (componentTransform != NULL) {
		componentTransform->mPosition.x = mPosition.x;
		componentTransform->mPosition.y = mPosition.y;
	}

}

void Component_Body::HandleEvent(Event * pEvent)
{
	if (pEvent->eType == EVENT_COLLISION) {
		
		/*
		CollisionEvent *collisionEvent = (CollisionEvent*)pEvent;
		GameObject *obj1 = collisionEvent->mpObjects[0];
		GameObject *obj2 = collisionEvent->mpObjects[1];

		if (obj1->mType == TYPE_BOMB && obj2->mType == TYPE_BOMB) {
			Component_BombCollider *pBC1 = (Component_BombCollider*)obj1->GetComponent(COMPONENT_BOMBCOLLIDER);
			Component_BombCollider *pBC2 = (Component_BombCollider*)obj2->GetComponent(COMPONENT_BOMBCOLLIDER);

			GameObject *objToKill = pBC1->mClock> pBC2->mClock?obj2:obj1;
			objToKill->mFlag = false;

		}
		*/
	}
}
