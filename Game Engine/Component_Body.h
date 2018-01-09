#pragma once
#include "Component.h"
#include "Vector2D.h"

class Shape;

class Component_Body : public Component
{
public:
	Component_Body();
	~Component_Body();
	void Update();
	void Serialize(FILE **fpp);
	void Initialize();
	void Integrate(float dt);
	void HandleEvent(Event *pEvent);

	Vector2D	mPrevPosition;
	Vector2D	mPosition;
	Vector2D	mVelocity;
	Shape		*mpShape;
};

