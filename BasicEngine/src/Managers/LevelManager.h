/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			LevelManager.h
Purpose:			LevelManager header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include "ObjectFactory.h"

enum Levels 
{
	MENU = 1,
	LEVEL1,
	LEVEL2,
	WIN,
	LOSE
};

class LevelManager
{
public:
	LevelManager();
	~LevelManager();
	void Update(float dt);
	void LoadLevel(Levels LTtemp);

public:
	int currentLevel;
};
