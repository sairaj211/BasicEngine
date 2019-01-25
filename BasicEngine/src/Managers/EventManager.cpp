/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			EventManager.cpp
Purpose:			EventManager implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "EventManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager *GOM;

Event::Event(EventType Type)
{
	mType = Type;
	mTimer = 0.0f;
}

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

void EventManager::BroadCastEvent(Event * pEvent)
{
	for (unsigned int i = 0; i < GOM->mGameObjects.size(); ++i)
		GOM->mGameObjects[i]->HandleEvent(pEvent);
}

void EventManager::BroadCastEventToSubscribe(Event * pEvent)
{
	auto &listOfSubscribers = mSubscribe[pEvent->mType];

	for (auto pGO : listOfSubscribers)
	{
		pGO->HandleEvent(pEvent);
	}
}

void EventManager::AddTimedEvent(Event * pEvent)
{
	mTimedEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime)
{

	// Loop through all timed events
	// Decrease timer by FrameTime
	// < 0 ? -> Fire Event

	std::list<Event *>::iterator it;

	it = mTimedEvents.begin();

	while (it != mTimedEvents.end())
	{
		Event *pEvent = *it;
		pEvent->mTimer -= FrameTime/1000.0f;
		if (pEvent->mTimer < 0.0f)
		{
			BroadCastEvent(pEvent);

			delete pEvent;
			it = mTimedEvents.erase(it);
		}
		else
			++it;
	}
}

void EventManager::Subscribe(EventType Type, GameObject * pGameObjectNewSubscriber)
{
	//std::list<GameObject *> &listOfSubscribes = mSubscribe[Type];
	auto &listOfSubscribers = mSubscribe[Type];

	for (auto pGO : listOfSubscribers)
		if (pGO == pGameObjectNewSubscriber)
			return;

	listOfSubscribers.push_back(pGameObjectNewSubscriber);
}

void EventManager::UnSubscribe(EventType Type, GameObject * pGameObjectUnsubscriber)
{
	auto &listOfSubscribers = mSubscribe[Type];
	auto it = std::find(listOfSubscribers.begin(), listOfSubscribers.end(), pGameObjectUnsubscriber);

	if (it == listOfSubscribers.end())
		return;

	listOfSubscribers.erase(it);
}
