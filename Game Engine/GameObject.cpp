#include "GameObject.h"
#include "Component_Sprite.h"
#include "Component_Transform.h"
#include "Component_Controller.h"
#include "Component_UpDown.h"
#include "Component_Animation.h"
#include "Component_Body.h"
#include "Component_Explosion.h"
#include "Component_BombCollider.h"
#include "Component_Timer.h"
#include "Component_AI.h"
#include "GameManagers.h"

extern GameManagers *gameManagers;

#define FLAG_ACTIVE			0x00000001

void GameObject::Update()
{
	for (int i = 0; i < mpComponentList.size(); ++i)
		mpComponentList[i]->Update();
}

Component* GameObject::GetComponent(ComponentType componentType)
{
	for (int i = 0; i < mpComponentList.size(); ++i) {
		if (mpComponentList[i]->mType == componentType)
			return mpComponentList[i];
	}

	return NULL;
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (int i = 0; i < mpComponentList.size(); ++i) {
		if (mpComponentList[i] != NULL)
			mpComponentList[i]->HandleEvent(pEvent);
	}

}

GameObject::GameObject()
{
	mFlag = FLAG_ACTIVE;												
	mType = TYPE_UNDEFINED;
	mNumberofBombs = 0;
}

GameObject::~GameObject()
{
	for (int i = 0; i < mpComponentList.size(); ++i) {
		delete mpComponentList[i];
	}
}

void GameObject::AddComponent_Sprite()
{
	Component_Sprite *spriteComponent = (Component_Sprite*)GetComponent(COMPONENT_SPRITE);

	if (spriteComponent == NULL) {
		spriteComponent = new Component_Sprite();
		mpComponentList.push_back(spriteComponent);
	}
	spriteComponent->mpWindowSurface = gameManagers->pwindowSurface;

	spriteComponent->mpOwner = this;
}

void GameObject::AddComponent_Transform()
{
	Component_Transform *transformComponent = (Component_Transform*)GetComponent(COMPONENT_TRANSFORM);
	if (transformComponent == NULL) {
		transformComponent = new Component_Transform();
		mpComponentList.push_back(transformComponent);
	}

	transformComponent->mpOwner = this;

	
}

void GameObject::AddComponent_Controller()
{
	Component_Controller *controllerComponent = (Component_Controller*)GetComponent(COMPONENT_CONTROLLER);
	if (controllerComponent == NULL) {
		controllerComponent = new Component_Controller();
		mpComponentList.push_back(controllerComponent);
	}
	controllerComponent->mpinputManager = gameManagers->mpInputManager;
	controllerComponent->mpOwner = this;

	
}

void GameObject::AddComponent_UpDown()
{
	Component_UpDown *upDownComponent = (Component_UpDown*)GetComponent(COMPONENT_UPDOWN);
	if (upDownComponent == NULL) {
		upDownComponent = new Component_UpDown();
		mpComponentList.push_back(upDownComponent);
	}
	upDownComponent->mpOwner = this;	
}

void GameObject::AddComponent_AI()
{
	Component_AI *aiComponent = (Component_AI*)GetComponent(COMPONENT_AI);
	if (aiComponent == NULL) {
		aiComponent = new Component_AI();
		mpComponentList.push_back(aiComponent);
	}
	aiComponent->mpOwner = this;
}

void GameObject::AddComponent_Animation()
{
	Component_Animation *animationComponent = (Component_Animation*)GetComponent(COMPONENT_ANIMATION);
	if (animationComponent == NULL) {
		animationComponent = new Component_Animation();
		mpComponentList.push_back(animationComponent);
	}
	animationComponent->mpOwner = this;
	
}

void GameObject::AddComponent_Body()
{
	Component_Body *animationComponent = (Component_Body*)GetComponent(COMPONENT_BODY);
	if (animationComponent == NULL) {
		animationComponent = new Component_Body();
		mpComponentList.push_back(animationComponent);
	}

	animationComponent->mpOwner = this;
	
}

void GameObject::AddComponent_Explosion()
{
	Component_Explosion *explosionComponent = (Component_Explosion*)GetComponent(COMPONENT_EXPLOSION);
	if (explosionComponent == NULL) {
		explosionComponent = new Component_Explosion();
		mpComponentList.push_back(explosionComponent);
	}
	explosionComponent->mpOwner = this;
	
}

void GameObject::AddComponent_BombCollider()
{
	Component_BombCollider *bombColliderComponent = (Component_BombCollider*)GetComponent(COMPONENT_BOMBCOLLIDER);
	if (bombColliderComponent == NULL) {
		bombColliderComponent = new Component_BombCollider();
		mpComponentList.push_back(bombColliderComponent);
	}
	bombColliderComponent->mpOwner = this;
	bombColliderComponent->mpPlacer = NULL;
}

void GameObject::AddComponent_Timer()
{
	Component_Timer *timerComponent = (Component_Timer*)GetComponent(COMPONENT_TIMER);
	if (timerComponent == NULL) {
		timerComponent = new Component_Timer();
		mpComponentList.push_back(timerComponent);
	}
	timerComponent->mpOwner = this;
}
