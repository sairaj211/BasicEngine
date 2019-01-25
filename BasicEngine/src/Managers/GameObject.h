/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			GameObject.h
Purpose:			GameObject header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include <vector>

class Transform;
class Sprite;
class Component;
class Event;
class Controller;

enum GameObjectType
{
	PLAYER = 1,
	ENEMY,
	BACKGROUND,
	ASTEROID,
	BULLET,
	MISSILESPAWN,
	BLACKHOLE,
	MENU,
	SCREEN
};

class GameObject
{
public:
	//GameObject();
	GameObject(GameObjectType mType);
	~GameObject();

	void Update(float dt);
	Component *AddComponent(unsigned int Type);
	Component *GetComponent(unsigned int Type);
	void HandleEvent(Event *pEvent);
	//void GetType();
public:
	/*Sprite *mpSprite;
	Transform *mpTrasform;
	Controller *mpController;*/
	GameObjectType ObjectType;
	std::vector<Component *> mComponents ;
	bool ActiveFlag;
};

