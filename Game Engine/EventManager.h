#pragma once
#include <list>
#include "Event.h"
#include "GameObject.h"
#include <unordered_map>

class EventManager
{
public:
	EventManager();
	~EventManager();

	void BroadCast(Event *pEvent);
	void BroadCastToSubscribers(Event *pEvent);
	void AddTimedEvent(Event *pEvent);
	void Subscribe(EventType et, GameObject *pGObj);
	void UnSubscribe(EventType et, GameObject *pGObj);
	void Update();
	
	std::unordered_map<EventType, std::vector<GameObject*>> mSubscriptions;
	std::vector<Event*> mpTimedEvents;
};

