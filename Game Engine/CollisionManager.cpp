#include "CollisionManager.h"
#include "Component_Body.h"

//////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////
CollisionManager::CollisionManager()
{
	Reset();
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c;
	mContacts.clear();
}

bool CollisionManager::CollisionTest(ShapeAABB *pShape1, ShapeAABB * pShape2)
{
	if (pShape1 == NULL || pShape2 == NULL) return false;
	bool r = StaticRectToStaticRect(&pShape1->mpOwnerBody->mPosition, pShape1->mWidth, pShape1->mHeight, &pShape2->mpOwnerBody->mPosition, pShape2->mWidth, pShape2->mHeight);
	if (r) {
		Contact *pNewContact = new Contact();
		pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
		mContacts.push_back(pNewContact);
	}

	return r;
}

bool CollisionManager::StaticRectToStaticRect(Vector2D * pRect0, float Width0, float Height0, Vector2D * pRect1, float Width1, float Height1)
{
	if (pRect0->x - Width0 / 2 <= pRect1->x + Width1 / 2 &&
		pRect0->x + Width0 / 2 >= pRect1->x - Width1 / 2 &&
		pRect0->y + Height0 / 2 >= pRect1->y - Height1 / 2 &&
		pRect0->y - Height0 / 2 <= pRect1->y + Height1 / 2)
		return true;
	return false;
}

