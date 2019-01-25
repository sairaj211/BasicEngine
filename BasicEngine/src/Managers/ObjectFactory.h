/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			ObjectFactory.h
Purpose:			ObjectFactory  header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include <string>

class GameObject;

class ObjectFactory
{
public:
	ObjectFactory();
	~ObjectFactory();

	GameObject *LoadObject(const char * pFileName);
	void LoadLevel(const char *pFileName);
	std::string resourcePath = "Res/";
};

