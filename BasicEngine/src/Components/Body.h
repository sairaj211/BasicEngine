/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Body.h
Purpose:			Body header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include <glm/glm.hpp>
#include"Component.h"
#include "CollisionManager.h"
#include "EventManager.h"

class Shape;

class MassDestruction :public Event
{
public:
	MassDestruction();
	~MassDestruction();
};


class Body: public Component
{
public:
	Body();
	~Body();

	void Update(float dt);
	void Serialize(FILE **);
	void Initilize();
	void Integrate(float Gravity, float DeltaTime);
	virtual void HandleEvent(Event *pEvent);

public:

	glm::vec3 mBodyPos,
		mPreBodyPos,
		mBodyVel,
		mBodyAcc,
		mBodyForce;

	float mInvMass, mMass;

	int lives = 3;
	Shape *pShape;

};

