#pragma once
#include "Shape.h"
#include <list>

class Contact {
public:
	Contact() {
		mpBodies[0] = mpBodies[1] = NULL;
	}

	Component_Body *mpBodies[2];
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Reset();
	bool CollisionTest(ShapeAABB *pShape1, ShapeAABB * pShape2);
	bool StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1);
	std::list<Contact *> mContacts;
};

