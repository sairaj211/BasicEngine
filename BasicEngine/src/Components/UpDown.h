/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			UpDown.h
Purpose:			UpDown header files
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

class GameObject;

class BulletHitEvent :public Event
{
public:
	BulletHitEvent();
	~BulletHitEvent();
};

class PlayerEnemyCollide :public Event
{
public:
	PlayerEnemyCollide();
	~PlayerEnemyCollide();
};

class StopUpdown : public Event
{
public:
	StopUpdown();
	~StopUpdown();
};

class UpDown: public Component
{
public:
	UpDown();
	~UpDown();

	void Update(float dt);
	void Serialize(FILE **);
	virtual void HandleEvent(Event *pEvent);

public:
	bool mGoingUp;
	float mTimer;
	int mTimerLimit;
	bool isUpDown;
};

