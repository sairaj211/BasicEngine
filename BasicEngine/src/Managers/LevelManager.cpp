/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			LevelManager.h
Purpose:			LevelManager implementaion files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "LevelManager.h"

extern ObjectFactory *gOF;
LevelManager::LevelManager()
{
	currentLevel = Levels::MENU;
}

LevelManager::~LevelManager()
{
}

void LevelManager::Update(float dt)
{
	
}

void LevelManager::LoadLevel(Levels LTtemp)
{
	switch (LTtemp)
	{
	case Levels::MENU:
		gOF->LoadLevel("Menu.txt");
		break;
	case Levels::LEVEL1:
		gOF->LoadLevel("Level1.txt");
		break;
	case Levels::LEVEL2:
		gOF->LoadLevel("Level2.txt");
		break;
	case Levels::WIN:
		gOF->LoadLevel("Win.txt");
		break;
	case Levels::LOSE:
		gOF->LoadLevel("Lose.txt");
		break;
	}
}
