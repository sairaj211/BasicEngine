/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			GameObjectManager.h
Purpose:			GameObjectManager header files
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
#include "GameObject.h"

class GameObject;
class VertexArray;
class IndexBuffer;
class Shader;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	 
	void Update(float dt);
	void DrawGameObjects(const VertexArray & va, const IndexBuffer & ib,  Shader* shader);
	void DestoryQ();
	GameObject* GetType(GameObjectType objType);

public:
	std::vector<GameObject *> mGameObjects;
	std::vector<GameObject *> mDestoryQ;
	
};

