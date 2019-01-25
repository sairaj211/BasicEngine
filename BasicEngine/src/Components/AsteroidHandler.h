/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			AsteroidHandler.h
Purpose:			AsteroidHandler header files
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
#include "BlackHole.h"
#include "GameObject.h"
#include "glm/glm.hpp"


class AsteroidBullerHit :public Event
{
public:
	AsteroidBullerHit();
	~AsteroidBullerHit();
};

class PlayerAsteroidCollide : public Event
{
public:
	PlayerAsteroidCollide();
	~PlayerAsteroidCollide();
};

class AsteroidMissileHit :public Event
{
public:
	AsteroidMissileHit();
	~AsteroidMissileHit();
};


class AsteroidCollisionResponse : public Event
{
public:
	AsteroidCollisionResponse();
	~AsteroidCollisionResponse();
};


class AsteroidHandler : public Component
{
public:
	AsteroidHandler();
	~AsteroidHandler();

	void getAsteroirdCount();
	virtual void Update(float dt);
	void Serialize(FILE **);
	virtual void HandleEvent(Event *pEvent);
	void HelperFunction();
	void FindPlayer();

public:
	GameObject *target;
	glm::vec3 normal, missileDir;
	bool homing;
	float dotProduct;
	GameObject *gTemp = nullptr;
	BlackHole *bTemp = nullptr;
	bool mGoingUp;
	float mTimer;
	bool mRotate;
	int mTimerLimit;
	bool ActiveFlag;

};