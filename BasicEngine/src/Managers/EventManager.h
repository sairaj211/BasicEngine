/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			EventManager.h
Purpose:			EventManager header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include <unordered_map>
#include <list>

class GameObject;

enum EventType
{
	COLLIDE = 1,
	PLAYERHIT,
	BULLETHIT,
	MISSILEHIT,
	DESTROYBULLET,
	COUNT,
	BLACKHOLEHEALTH,
	WEAPONUPGRADE,
	RUNRUN,
	SPAWNASTEROIDS,
	ASTEROIDCOLLISIONRESPONSE,
	STOPUPDOWN,
	NUM
};

class Event
{
public:
	Event(EventType Type);
	virtual ~Event() {}

public:
	float mTimer;
	EventType mType;

};


class EventManager
{
public:
	EventManager();
	~EventManager();
public:
	void BroadCastEvent(Event *pEvent);
	void BroadCastEventToSubscribe(Event *pEvent);
	void AddTimedEvent(Event *pEvent);
	void Update(float FrameTime);
	void Subscribe(EventType Type, GameObject *pGameObject);
	void UnSubscribe(EventType Type, GameObject *pGameObjectUnsubscriber);

public:
	std::list<Event *>mTimedEvents;

	std::unordered_map < EventType, std::list<GameObject *>> mSubscribe;
};