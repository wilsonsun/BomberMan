#include "Component_Animation.h"
#include "GameObject.h"
#include "Component_Sprite.h"
#include "GameManagers.h"
#include <SDL.h>

extern GameManagers *gameManagers;

Component_Animation::Component_Animation() : Component(COMPONENT_ANIMATION)
{
	mTimer = 0;
}


Component_Animation::~Component_Animation()
{
}

void Component_Animation::Update()
{
	mTimer ++;
	if (mTimer < 5) 
		return;

	mTimer = 0;
	Component_Sprite *pSt = (Component_Sprite *)mpOwner->GetComponent(COMPONENT_SPRITE);
	if (pSt == NULL) {
		printf("Component_Animation cannot get Component_Sprite\n");
		return;
	}

	if (mpOwner->mIsMoving) {
		if (pSt->mImagePosX >= 2)
			pSt->mImagePosX = -1;
		
		pSt->mImagePosX++;
	}
	else {
		pSt->mImagePosX = 1;
	}
}

void Component_Animation::Serialize(FILE ** fpp)
{
}

void Component_Animation::HandleEvent(Event * pEvent)
{
}
