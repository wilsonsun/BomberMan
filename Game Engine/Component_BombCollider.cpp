#pragma once
#include "Component_BombCollider.h"
#include "Component_Controller.h"
#include "GameManagers.h"


extern GameManagers *gameManagers;

Component_BombCollider::Component_BombCollider(): Component(COMPONENT_BOMBCOLLIDER), mActiveFLAG(false), mClock(0.0)
{
}

Component_BombCollider::~Component_BombCollider()
{
}

void Component_BombCollider::Update()
{
	mClock++;
	if (!mActiveFLAG) {
		// Owner's Shape
		Component_Body *bombBody = (Component_Body*)mpOwner->GetComponent(COMPONENT_BODY);
		ShapeAABB *bombShape = (ShapeAABB*)bombBody->mpShape;

		// Bomb's Shape
		if (mpPlacer == NULL) return;
		Component_Body *placerBody = (Component_Body*)mpPlacer->GetComponent(COMPONENT_BODY);
		if (placerBody == NULL) return;
		ShapeAABB *placerShape = (ShapeAABB*)placerBody->mpShape;
		
		bool r = gameManagers->mpPhysicsManager->mpCollisionMananger->CollisionTest(bombShape, placerShape);
		if (!r) {
			mActiveFLAG = true;
			Component_Controller *pContro = (Component_Controller*)mpPlacer->GetComponent(COMPONENT_CONTROLLER);
			if (pContro == NULL) return;
			pContro->mbombColliderActive = true;
			pContro->mInCurBomb = false;
		}
	}
}
