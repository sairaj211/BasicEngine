/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			AsteroidHandler.cpp
Purpose:			AsteroidHandler implementation
Language:			c++ and g cc compiler
Platform:			g cc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "AsteroidHandler.h"
#include "GameObjectManager.h"
#include "BlackHole.h"
#include "Body.h"
#include "Transform.h"
#include "Missile.h"
#include "Math2D.h"
#include "Matrix2D.h"
#include <iostream>

extern GameObjectManager *GOM;

extern EventManager *gEM;

#define ASTEROID_SPEED 0.10f

AsteroidHandler::AsteroidHandler() : Component(ASTEROIDHAN)
{
	ActiveFlag = true;
}

AsteroidHandler::~AsteroidHandler()
{
}



AsteroidBullerHit::AsteroidBullerHit() : Event(BULLETHIT)
{
}

AsteroidBullerHit::~AsteroidBullerHit()
{
}

PlayerAsteroidCollide::PlayerAsteroidCollide() : Event (PLAYERHIT)
{
}

PlayerAsteroidCollide::~PlayerAsteroidCollide()
{
}


AsteroidMissileHit::AsteroidMissileHit() : Event (MISSILEHIT)
{
}

AsteroidMissileHit::~AsteroidMissileHit()
{
}


AsteroidCollisionResponse::AsteroidCollisionResponse() :Event(ASTEROIDCOLLISIONRESPONSE)
{
}

AsteroidCollisionResponse::~AsteroidCollisionResponse()
{
}



void AsteroidHandler::getAsteroirdCount()
{
	for (unsigned int i = 0; i < GOM->mGameObjects.size(); i++)
	{
		if (GOM->mGameObjects[i]->ObjectType == BLACKHOLE)
		{
			bTemp = static_cast<BlackHole *>(GOM->mGameObjects[i]->GetComponent(BLACKHOLE));
		}
	}
}


	void AsteroidHandler::Update(float dt)
{
		/*
	mTimer += dt;
	if (mTimer > mTimerLimit)
	{
		mGoingUp = !mGoingUp;
		mRotate = !mGoingUp;
		mTimer = 0;
	}

	Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));

	if (nullptr != pBody)
	{
		if (true == mGoingUp) {
				pBody->mBodyPos.x -= 4.0f;	

		}
		else {
			pTr->mAngle -= 2.5f;

		}

	}*/
		int ranNum = rand() % 10;

	// Homing Missile Behavior

		FindPlayer();

		if (!homing) {
			return;
		}
		homing = false;

		if (target == NULL)
		{
			FindPlayer();
		}

		Body *targetBody = static_cast<Body*>(target->GetComponent(BODY));
		Transform *targetTrans = static_cast<Transform*>(target->GetComponent(TRANSFORM));

		Body *asteroidBody = static_cast<Body*>(this->mpOwner->GetComponent(BODY));
		Transform *asteroidTrans = static_cast<Transform*>(this->mpOwner->GetComponent(TRANSFORM));

		Matrix2D rotation;
		Vector2D target_vector, normalized_target_vector, normal;
		float cos_angle, angle, turn;


		Vector2D asteroidPosition;
		Vector2DSet(&asteroidPosition, asteroidBody->mBodyPos.x, asteroidBody->mBodyPos.y);

		Vector2D targetPosition;

		if (ranNum % 2 == 0) {
			Vector2DSet(&targetPosition, targetBody->mBodyPos.x + 200.0f, targetBody->mBodyPos.y + 200.0f);
		}
		else
		{
			Vector2DSet(&targetPosition, targetBody->mBodyPos.x + 50.0f, targetBody->mBodyPos.y + 50.0f);
		}


		// target vector
		Vector2DSub(&target_vector, &targetPosition, &asteroidPosition);
		// unit vector in dir of target
		Vector2DNormalize(&normalized_target_vector, &target_vector);


		Vector2D asteroidVel;
		Vector2DSet(&asteroidVel, asteroidBody->mBodyVel.x, asteroidBody->mBodyVel.y);
		cos_angle = Vector2DDotProduct(&normalized_target_vector, &asteroidVel);

		angle = glm::radians(acosf(cos_angle));
		//calculating normal
		Matrix2DRotRad(&rotation, 90);
		Matrix2DMultVec(&normal, &rotation, &asteroidVel);
		// DOT product for turning
		turn = Vector2DDotProduct(&normal, &target_vector);
		if (turn > 0)
		{

			asteroidTrans->mAngle += glm::degrees(angle);

			Vector2D asteroidnewVel;
			asteroidnewVel.x = asteroidBody->mBodyVel.x;
			asteroidnewVel.y = asteroidBody->mBodyVel.y;

			Vector2DFromAngleDeg(&asteroidnewVel, (asteroidTrans->mAngle));
			Vector2DScale(&asteroidnewVel, &asteroidnewVel, 0.75f);
			asteroidBody->mBodyVel.x = asteroidnewVel.x;
			asteroidBody->mBodyVel.y = asteroidnewVel.y;
		}
		else
		{
			asteroidTrans->mAngle -= glm::degrees(angle);
			Vector2D asteroidnewVel;
			asteroidnewVel.x = asteroidBody->mBodyVel.x;
			asteroidnewVel.y = asteroidBody->mBodyVel.y;

			Vector2DFromAngleDeg(&asteroidnewVel, (asteroidTrans->mAngle));
			Vector2DScale(&asteroidnewVel, &asteroidnewVel, 0.75f);
			asteroidBody->mBodyVel.x = asteroidnewVel.x;
			asteroidBody->mBodyVel.y = asteroidnewVel.y;

		}

		asteroidBody->mBodyVel.x = cosf((asteroidTrans->mAngle + 90)* 3.14f / 180.0f)*ASTEROID_SPEED;
		asteroidBody->mBodyVel.y = sinf((asteroidTrans->mAngle + 90)* 3.14f / 180.0f)*ASTEROID_SPEED;

		//std::cout << "vel x = " << asteroidBody->mBodyVel.x << std::endl;
		//std::cout << "vel y = " << asteroidBody->mBodyVel.y << std::endl;


}

void AsteroidHandler::Serialize(FILE **fpp)
{
	gEM->Subscribe(BULLETHIT, this->mpOwner);
	gEM->Subscribe(PLAYERHIT, this->mpOwner);
	gEM->Subscribe(MISSILEHIT, this->mpOwner);
	gEM->Subscribe(ASTEROIDCOLLISIONRESPONSE, this->mpOwner);
}

void AsteroidHandler::HandleEvent(Event * pEvent)
{
	if (BULLETHIT == pEvent->mType)
	{
		HelperFunction();
		this->ActiveFlag = false;
		bTemp->Asteroid_Count--;
		bTemp->Asteroid_Destoryed++;
		std::cout << "Asteroid Destroyed = " << bTemp->Asteroid_Destoryed << std::endl;
		GOM->mDestoryQ.push_back(this->mpOwner);
	}

	if (PLAYERHIT == pEvent->mType)
	{
		HelperFunction();
		this->ActiveFlag = false;
		bTemp->Asteroid_Count--;
		bTemp->Asteroid_Destoryed++;
		std::cout << "Asteroid Destroyed = " << bTemp->Asteroid_Destoryed << std::endl;
		GOM->mDestoryQ.push_back(this->mpOwner);
	}

	if (MISSILEHIT == pEvent->mType)
	{
		HelperFunction();
		this->ActiveFlag = false;
		bTemp->Asteroid_Count--;
		bTemp->Asteroid_Destoryed++;
		std::cout << "Asteroid Destroyed = " << bTemp->Asteroid_Destoryed << std::endl;
		GOM->mDestoryQ.push_back(this->mpOwner);
	}

	if (ASTEROIDCOLLISIONRESPONSE == pEvent->mType)
	{

	}



}

void AsteroidHandler::HelperFunction()
{
	//AsteroidDestroyedEvent *astDestroyed = new AsteroidDestroyedEvent();
	//gEM->BroadCastEvent(astDestroyed);
	//MissileHItEvent *mHit = new MissileHItEvent();

	for (unsigned int i = 0; i < GOM->mGameObjects.size(); i++)
	{
		if (GOM->mGameObjects[i]->ObjectType == MISSILESPAWN) {
			Missile *mTemp = static_cast<Missile *>(GOM->mGameObjects[i]->GetComponent(MISSILE));
			mTemp->target = nullptr;
		}
	}
}

void AsteroidHandler::FindPlayer()
{
	this->target = nullptr;
	for (auto gameObjects : GOM->mGameObjects)
	{
		if (gameObjects->ObjectType == PLAYER) {
			//AsteroidHandler *temp = static_cast<AsteroidHandler *> (gameObjects->GetComponent(ASTEROIDHAN));
			//if (temp->ActiveFlag == true) {
				homing = true;
				if (!target) {
					target = gameObjects;
					break;
				}
		}
	}
	
}
