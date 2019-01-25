/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Missile.h
Purpose:			Missile header files
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
#include "glm/glm.hpp"
#include "BlackHole.h"
#include "GameObject.h"

class MissileHItEvent :public Event
{
public:
	MissileHItEvent();
	~MissileHItEvent();
};


class Missile : public Component
{
public:
	Missile();
	~Missile();

	void CreateMissile();
	virtual void Update(float dt);
	virtual void Serialize(FILE **fpp);
	virtual void HandleEvent(Event *pEvent);
	void FindTgt();

public:
	GameObject *target;
	glm::vec3 normal, missileDir;
	bool homing;
	float dotProduct;
};
