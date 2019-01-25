/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Controller.h
Purpose:			Controller header files
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
#include "Body.h"
#include "Transform.h"
#include "BlackHole.h"
#include "GameObject.h"	


class GameObject;

class PlayerHitEvent :public Event
{
public:
	PlayerHitEvent();
	~PlayerHitEvent();
};


class WeaponUpgrade :public Event
{
public:
	WeaponUpgrade();
	~WeaponUpgrade();
};


class Controller : public Component
{
public:
	Controller();
	~Controller();


	void Update(float);
	virtual	void Serialize(FILE **fpp);
	virtual void HandleEvent(Event *pEvent);
	void CreateBullet(Body *, Transform*);
	void CreateMissile();
	void GetBlackHoleHealth();
	bool isColor=false;

	bool powerUp;
	int lives = 3;
};

