/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Body.cpp
Purpose:			Body implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include <iostream>
#include "GameObjectManager.h"
#include "ObjectFactory.h"
#include "BlackHole.h"

extern EventManager *gEM;
extern GameObjectManager *GOM;
extern ObjectFactory *gOF;
MassDestruction::MassDestruction() : Event(RUNRUN)
{
}

MassDestruction::~MassDestruction()
{
}


Body::Body() :Component(BODY)
{

	mBodyPos = glm::vec3(0.0f);
	mPreBodyPos = glm::vec3(0.0f);
	mBodyVel = glm::vec3(0.0f);
	mBodyAcc = glm::vec3(0.0f);
	mBodyForce = glm::vec3(0.0f);
	 
	mMass = mInvMass = 0.0f;

	pShape = nullptr;
}

Body::~Body()
{
}

void Body::Update(float dt)
{
}

void Body::Serialize(FILE **fpp)
{
	if (this->mpOwner->ObjectType == MISSILESPAWN)
	{
		gEM->Subscribe(MISSILEHIT, this->mpOwner);
	}
	
	gEM->Subscribe(RUNRUN, this->mpOwner);

	fscanf_s(*fpp, "%f\n", &mMass);
	if(mMass)
		mInvMass = 1.0f / mMass;
	else 
		mInvMass = 0.0f;

	char shapeType[256] = { 0 };
	fscanf_s(*fpp, "%255s\n", shapeType, sizeof(shapeType));
	if (0 == strcmp(shapeType, "CIRCLE"))
	{
		float radius;
		fscanf_s(*fpp, "%f\n", &radius);
		pShape = new ShapeCircle(radius);
		pShape->mpOwnerBody = this;
		
	}
	else if (0 == strcmp(shapeType, "AABB"))
	{	
		float mLeft, mTop, mRight, mBottom;
		fscanf_s(*fpp, "%f %f %f %f \n", &mLeft, &mTop, &mRight, &mBottom);
		pShape = new ShapeAABB(mTop, mBottom, mLeft, mRight);
		pShape->mpOwnerBody = this;		
	}
}

void Body::Initilize()
{
	Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));

	if (nullptr != pTr) {
		
		mBodyPos = mPreBodyPos = pTr->mPos;
	}
}

void Body::Integrate(float Gravity, float DeltaTime)
{

	mPreBodyPos = mBodyPos;

	mBodyForce.y += Gravity;

	mBodyAcc = mBodyForce * mInvMass;

	mBodyAcc = mBodyAcc / 5000.0f ;

	//std::cout << "acc x  = " << mBodyAcc.x << std::endl;
	//std::cout << "acc y = " << mBodyAcc.y << std::endl;
	if (this->mpOwner->ObjectType == PLAYER)
		mBodyVel = (mBodyAcc * DeltaTime + mBodyVel) * 0.99f;
	else
		mBodyVel = (mBodyAcc * DeltaTime + mBodyVel) ;

	mBodyPos = mBodyVel * DeltaTime + mBodyPos;

	mBodyForce = glm::vec3(0.0f);

	Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));

	if (nullptr != pTr) {

		pTr->mPos = mBodyPos;
	}
}

void Body::HandleEvent(Event * pEvent)
{
	if (RUNRUN == pEvent->mType)
	{

		if (this->mpOwner->ObjectType != BLACKHOLE && this->mpOwner->ObjectType != PLAYER)
		{
			GOM->mDestoryQ.push_back(this->mpOwner);
		}
		if (this->mpOwner->ObjectType != BLACKHOLE)
		{
			BlackHole *bTemp = static_cast<BlackHole *>(this->mpOwner->GetComponent(ASTEROIDSPAWNER));
			//bTemp->Asteroid_Count = 0;
			std::cout << "Spawning Asteriods in 2 SEC" << std::endl;
		}
	}

	
}

