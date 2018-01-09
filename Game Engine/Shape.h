#pragma once
#include "Component_Body.h"

class Shape
{
public:
	enum SHAPE_TYPE {
		SHAPE_AABB,
		SHAPE_INVALID
	};

	Shape(SHAPE_TYPE Type);
	virtual ~Shape();

	Component_Body* mpOwnerBody;
	SHAPE_TYPE mShapeType;
};


class ShapeAABB :public Shape {
public:
	ShapeAABB() :Shape(SHAPE_AABB) { mWidth, mHeight = 0.0f; }
	~ShapeAABB();

	float mWidth, mHeight;
};
