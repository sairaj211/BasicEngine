/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Transform.cpp
Purpose:			Transform implementation 
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.h"
extern Renderer* gRenderer;

glm::vec3 axis(0.0f,0.0f,1.0f);

Transform::Transform() : Component(TRANSFORM)
{
	mPos = glm::vec3(0.0f);
	mScale = glm::vec3(0.0f);
	mAngle = 0.0f;
}


Transform::~Transform()
{
}

void Transform::Update(float dt)
{
	//if()
	mTransform = glm::mat4(1.0f);
	mTransform = glm::translate(mTransform, mPos);
	mTransform = glm::rotate(mTransform, glm::radians(mAngle), axis);
	mTransform = glm::scale(mTransform, mScale);	
}

void Transform::DebugUpdate()
{
	mTransform = glm::mat4(1.0f);
	mTransform = glm::translate(mTransform, mPos);
	//mTransform = glm::rotate(mTransform, glm::radians(mAngle), axis);
	mTransform = glm::scale(mTransform, mScale);
}

void Transform::Serialize(FILE **fpp)
{
	//initial cooridnates
	fscanf_s(*fpp, "%f %f %f %f\n", &mPos.x, &mPos.y, &mScale.x, &mScale.y);
}
