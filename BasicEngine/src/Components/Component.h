/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Component.h
Purpose:			Component header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include "stdio.h"


enum COMPONENT_TYPE
{
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	UPDOWN,
	BODY,
	WRAPA,
	WRAPD,
	MISSILE,
	ASTEROIDSPAWNER,
	ASTEROIDHAN
};

class GameObject;
class Event;

class Component
{
public:
	Component(unsigned int Type);
	virtual ~Component();

	virtual void Update(float dt) = 0;
	unsigned int GetType() { return mType; }

	virtual	void Serialize(FILE **fpp) { }
	virtual void HandleEvent(Event *pEvent) {}

public:
	GameObject *mpOwner;

private:
	unsigned int mType;
};

