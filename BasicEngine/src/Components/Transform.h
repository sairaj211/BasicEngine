/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Transform.h
Purpose:			Transform  header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once
#include"Component.h"
#include "glm/glm.hpp"


class Transform: public Component
{
public:
	Transform();
	~Transform();

	void Update(float);
	void DebugUpdate();
	void Serialize(FILE **);

public:
	//float mPosX, mPosY;
	glm::vec3 mPos, mScale;
	glm::mat4 mTransform;
	float mAngle;
};

