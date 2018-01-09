#pragma once
#include "InputManager.h"
#include "GameObject.h"
#include "Component.h"

class Component_Controller : public Component
{
public:
	Component_Controller();
	~Component_Controller();
	void Update();
	void Serialize(FILE **fpp);
	void HandleEvent(Event *pEvent);

	InputManager	*mpinputManager;
	bool mControllerSwitches[4];
	bool mbombColliderActive;
	bool mInCurBomb;
	float SPEED;
	int EXPLOSIONLENGTH;
private:
	GameObject *mpLastBomb;
	void EnableControls();

};

