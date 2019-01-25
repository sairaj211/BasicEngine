/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			OutOfBound.cpp
Purpose:			OutOfBound implementation files(to check if object is out of bound, if yes then destroy object )
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Outofbound.h"
#include "GameObject.h"
#include "Body.h"
#include "GameObjectManager.h"

extern GameObjectManager *GOM;

extern EventManager *gEM;

//TargetHit::TargetHit() :Event(BULLETHIT)
//{
//}
//
//TargetHit::~TargetHit()
//{
//}

Outofbound::Outofbound() : Component(WRAPD)
{
}

Outofbound::~Outofbound()
{
}

DestroyBullet::DestroyBullet() : Event(DESTROYBULLET)
{
}

DestroyBullet::~DestroyBullet()
{
}



void Outofbound::Serialize(FILE **fpp)
{
	gEM->Subscribe(DESTROYBULLET, this->mpOwner);
}


void Outofbound::Update(float dt)
{
	Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));

	//Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	//printf("angle = %f\n", pTr->mAngle);
	//printf("pBody .x = %f\n", pBody->mBodyPos.x);
	//printf("pBody .y = %f\n", pBody->mBodyPos.y);


	if (pBody->mBodyPos.y > 610.0f || pBody->mBodyPos.y < 0.0f)
	{
		GOM->mDestoryQ.push_back(this->mpOwner);
	}


	if (pBody->mBodyPos.x > 810.0f || pBody->mBodyPos.x < 0.0f)
	{
		GOM->mDestoryQ.push_back(this->mpOwner);
	}

}

void Outofbound::HandleEvent(Event * pEvent)
{
	if (DESTROYBULLET == pEvent->mType)
	{
		GOM->mDestoryQ.push_back(this->mpOwner);
	}
}

