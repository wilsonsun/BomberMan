#include "Component_Transform.h"
#include "ComponentList.h"
#include <stddef.h>

Component_Transform::Component_Transform() : Component(COMPONENT_TRANSFORM)
{
	mPosition.x = 0.0f;
	mPosition.y = 0.0f;
	mpOwner = NULL;
}

Component_Transform::~Component_Transform()
{
}

void Component_Transform::Update()
{
}

void Component_Transform::Serialize(FILE ** fpp)
{
	fscanf_s(*fpp, "%f %f\n", &mPosition.x, &mPosition.y);
}

