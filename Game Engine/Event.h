#pragma once

class GameObject;

enum EventType {
	EVENT_COLLISION,
	EVENT_EXPLODSION,
	EVENT_DISMISS,
	EVENT_PLAYERHIT
};

class Event
{
public:
	Event(EventType Type);
	~Event();
	EventType eType;
	float mTimer;
	GameObject *mpOwner;
};

