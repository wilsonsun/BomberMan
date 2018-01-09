#include "EventManager.h"
#include "GameManagers.h"

extern GameManagers *gameManagers;

EventManager::EventManager()
{
}


EventManager::~EventManager()
{
}

void EventManager::BroadCast(Event * pEvent)
{
	for (auto obj : gameManagers->mpGameObjectManager->gameInstancesList)
		obj->HandleEvent(pEvent);
}

void EventManager::BroadCastToSubscribers(Event * pEvent)
{

	std::vector<GameObject*> &listOfSubscribers = mSubscriptions[pEvent->eType];
	for (int i = 0; i < listOfSubscribers.size(); ++i)
		listOfSubscribers[i]->HandleEvent(pEvent);

	/*
	for (auto obj : listOfSubscribers)
		obj->HandleEvent(pEvent);
		*/
	/*
	std::list<GameObject*>::iterator it;
	std::list<GameObject*> &listOfSubscribers = mSubscriptions[pEvent->eType];
	for (it = listOfSubscribers.begin(); it != listOfSubscribers.end(); ++it)
		(*it)->HandleEvent(pEvent);
		*/

	/*
	std::list<GameObject*> &listOfSubscribers = mSubscriptions[pEvent->eType];
	for (auto obj : listOfSubscribers) {
		//if (obj == NULL) continue;
		obj->HandleEvent(pEvent);
	}
	*/
	/*
	std::list<GameObject*> &listOfSubscribers = mSubscriptions[pEvent->eType];
	std::list<GameObject*>::iterator it, itEnd, itTemp;

	it = listOfSubscribers.begin();
	itEnd = listOfSubscribers.end();

	while (it != itEnd) {
		(*it)->HandleEvent(pEvent);
			++it;
	}
	*/
}

void EventManager::AddTimedEvent(Event * pEvent)
{
	mpTimedEvents.push_back(pEvent);
}

void EventManager::Subscribe(EventType et, GameObject *pGObj)
{
	std::vector<GameObject*> &listOfSubscribers = mSubscriptions[et];

	if (std::find(listOfSubscribers.begin(), listOfSubscribers.end(), pGObj) == listOfSubscribers.end()) {
		listOfSubscribers.push_back(pGObj);
	}
}

void EventManager::UnSubscribe(EventType et, GameObject * pGObj)
{
	std::vector<GameObject*> &listOfSubscribers = mSubscriptions[et];

	for (int i = 0; i < listOfSubscribers.size(); ++i) {
		if (listOfSubscribers[i] == pGObj)
			listOfSubscribers.erase(listOfSubscribers.begin()+i);
	}
}

void EventManager::Update()
{

	float frameTime = gameManagers->mpFrameRateController->GetFrameTime() / 1000.0f;

	for (int i = 0; i < mpTimedEvents.size(); ++i) {
		mpTimedEvents[i]->mTimer -= frameTime;

		if (mpTimedEvents[i]->mTimer <= 0.0f) {
			BroadCastToSubscribers(mpTimedEvents[i]);
			delete mpTimedEvents[i];
			mpTimedEvents.erase(mpTimedEvents.begin() + i);
		}
	}
	/*
	std::list<Event*>::iterator it, itEnd, itTemp;

	it = mpTimedEvents.begin();
	itEnd = mpTimedEvents.end();
	float frameTime = gameManagers->mpFrameRateController->GetFrameTime()/1000.0f;

	while (it != itEnd) {
		Event *pEvent = *it;

		pEvent->mTimer -= frameTime;

		if (pEvent->mTimer <= 0.0f) {
			BroadCastToSubscribers(pEvent);
			//BroadCast(pEvent);
			delete pEvent;
			itTemp = it;
			++itTemp;
			mpTimedEvents.erase(it);
			it = itTemp;
		}
		else {
			++it;
		}
	}
	*/
}
