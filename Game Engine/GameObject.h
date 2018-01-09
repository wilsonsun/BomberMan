#pragma once
#include <SDL.h>
#include <vector>
#include "InputManager.h"
#include "GameObjectTypeList.h"
#include "Component.h"
#include "Vector2D.h"
#include "PlayerState.h"
#include "FireState.h"
#include "Event.h"

class GameObject
{
public:
	GameObjectType				mType;
	bool						mFlag;						// Bit mFlag, used to indicate if the object instance is active or not
	PlayerState					mState;						// Player's current State
	bool						mIsMoving;					// Flag that indicates if the player is moving
	SDL_Rect					mRect;
	FIRE_STATE					mFireState;
	int							mTextureID;
	int							mNumberofBombs;
	//int							mMaxBombs;

	GameObject();
	~GameObject();

	std::vector<Component *> mpComponentList;
	void Update();
	Component* GetComponent(ComponentType componentType);
	void HandleEvent(Event *pEvent);


	void GameObject::AddComponent_Sprite();
	void GameObject::AddComponent_Transform();
	void GameObject::AddComponent_Controller();
	void GameObject::AddComponent_UpDown();
	void GameObject::AddComponent_Animation();
	void GameObject::AddComponent_Body();
	void GameObject::AddComponent_Explosion();
	void GameObject::AddComponent_BombCollider();
	void GameObject::AddComponent_Timer();
	void GameObject::AddComponent_AI();
};

