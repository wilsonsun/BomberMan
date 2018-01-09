#include "Event.h"
#include "GameObject.h"
#include <iostream>

Event::Event(EventType Type)
{
	eType = Type;
	mTimer = 0.0f;
	mpOwner = NULL;
}

Event::~Event()
{
}
