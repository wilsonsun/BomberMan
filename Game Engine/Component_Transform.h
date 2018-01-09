#pragma once
#include <iostream>
#include "Vector2D.h"
#include "Component.h"

class Component_Transform : public Component
{
public:
	Component_Transform();
	~Component_Transform();
	void Update();
	void Serialize(FILE **fpp);

	Vector2D	mPosition;			// Current position
};

