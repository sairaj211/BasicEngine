/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			BlackHole.h
Purpose:			BlackHole header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include "Component.h"
#include "EventManager.h"

class BlackHoleHitEvent :public Event
{
public:
	BlackHoleHitEvent();
	~BlackHoleHitEvent();
};

class ResetAsteroidsEvent : public Event
{
public:
	ResetAsteroidsEvent();
	~ResetAsteroidsEvent();
};


class BlackHole : public Component
{
public:
	BlackHole();
	~BlackHole();

	virtual void Update(float dt);
	void CreateAsteorid();
	void Serialize(FILE **);
	virtual void HandleEvent(Event *pEvent);
	
public:
	int health;
	static int Asteroid_Count, Asteroid_Destoryed;
};