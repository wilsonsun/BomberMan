#include "Shape.h"

Shape::Shape(SHAPE_TYPE Type)
{
	mShapeType = Type;
	mpOwnerBody = NULL;
}

Shape::~Shape()
{
}

ShapeAABB::~ShapeAABB()
{
}
