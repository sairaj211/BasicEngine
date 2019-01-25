/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			UpDown.cpp
Purpose:			UpDown implementaion files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "UpDown.h"
#include "GameObject.h"
#include "FrameRateController.h"
#include "EventManager.h"
#include "Body.h"
#include "GameObjectManager.h"

extern GameObjectManager *GOM;

extern FrameRateController *gpFRC;
extern EventManager *gEM;



BulletHitEvent::BulletHitEvent() : Event(BULLETHIT)
{
}

BulletHitEvent::~BulletHitEvent()
{
}

PlayerEnemyCollide::PlayerEnemyCollide() : Event(PLAYERHIT)
{
}

PlayerEnemyCollide::~PlayerEnemyCollide()
{
}


UpDown::UpDown() : Component(UPDOWN)
{
	mGoingUp = true;
	mTimer = 0;
	mTimerLimit = 0;
	isUpDown = true;
}

UpDown::~UpDown()
{
}

void UpDown::Update(float dt)
{
	mTimer += dt;
	if (mTimer > mTimerLimit)
	{
		mGoingUp = !mGoingUp;
		mTimer = 0;
	}

	//Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));
	Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));

	if (isUpDown)
	{
		if (nullptr != pBody)
		{
			if (true == mGoingUp)
				pBody->mBodyPos.x -= 2.5f;
			else
				pBody->mBodyPos.x += 2.5f;

		}
	}

}

void UpDown::Serialize(FILE **fpp)
{
	gEM->Subscribe(BULLETHIT, this->mpOwner);
	gEM->Subscribe(PLAYERHIT, this->mpOwner);
	gEM->Subscribe(STOPUPDOWN, this->mpOwner);
	int goingUp, timerLimit;

	fscanf_s(*fpp, "%i %i\n", &goingUp, &timerLimit);

	mGoingUp = (bool)goingUp;
	mTimerLimit = timerLimit;

}

void UpDown::HandleEvent(Event * pEvent)
{
	if (BULLETHIT == pEvent->mType)
	{
		GOM->mDestoryQ.push_back(this->mpOwner);
	}

	if (PLAYERHIT == pEvent->mType)
	{
		////Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));
		//Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		//if (pBody != nullptr)
		//	pBody->mBodyPos.x += 50.f;
		GOM->mDestoryQ.push_back(this->mpOwner);
		
	}
	if (STOPUPDOWN == pEvent->mType)
	{
		this->isUpDown = false;
	}
	
}

StopUpdown::StopUpdown() : Event(STOPUPDOWN)
{
}

StopUpdown::~StopUpdown()
{
}
