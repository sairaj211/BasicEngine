/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			WrapA.cpp
Purpose:			WrapA implementation files (wrap around the screen functionality)
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "WrapA.h"
#include "Body.h"
#include "GameObject.h"
#include <stdio.h>
#include "Transform.h"
#include "GameObjectManager.h"

extern GameObjectManager *GOM;


WrapA::WrapA() : Component(WRAPA)
{
}

WrapA::~WrapA()
{
}


void WrapA::Update(float dt)
{
	Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));

	//Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	//printf("angle = %f\n", pTr->mAngle);
	//printf("pBody .x = %f\n", pBody->mBodyPos.x);
	//printf("pBody .y = %f\n", pBody->mBodyPos.y);


	if (pBody->mBodyPos.y > 610.0f)
	{
		pBody->mBodyPos.y = 0.0f;
	}

	if (pBody->mBodyPos.y < 0.0f)
	{
		pBody->mBodyPos.y = 600.0f;
	}

	if (pBody->mBodyPos.x > 810.0f )
	{
		pBody->mBodyPos.x = 0.0f;
	}

	if (pBody->mBodyPos.x < 0.0f)
	{
		pBody->mBodyPos.x = 800.0f;
	}
}




