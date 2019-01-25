/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Missile.cpp
Purpose:			Missile implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Missile.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Body.h"
#include "Transform.h"
#include "ObjectFactory.h"
#include "Math2D.h"
#include "Matrix2D.h"
#include "AsteroidHandler.h"
#include "BlackHole.h"
extern ObjectFactory *gOF;
extern GameObjectManager *GOM;
GameObject *gamObject;
extern EventManager *gEM;

float MISSILESPEED = 0.45f;
#define MISSILE_SPEED 0.25f
#define MISSILE_OFFSET 0.11
#define MISSILE_TURNRATE Pi/2.0f

Missile::Missile(): Component(MISSILE)
{
	
}

Missile::~Missile()
{
}


MissileHItEvent::MissileHItEvent() : Event(MISSILEHIT)
{
}

MissileHItEvent::~MissileHItEvent()
{
}


void Missile::CreateMissile()
{
	homing = false;
	GameObject *ship = nullptr;
	ship = GOM->GetType(PLAYER);
	if (ship != nullptr) {
		Body *shipBody = static_cast<Body *>(ship->GetComponent(BODY));
		Transform *shipTrans = static_cast<Transform *>(ship->GetComponent(TRANSFORM));
	


	GameObject *pBullet = gOF->LoadObject("Archetypes/Missile.txt");
	Body *pBulletBody = static_cast<Body*>(pBullet->GetComponent(BODY));
	Transform *pBulletTrans = static_cast<Transform*>(pBullet->GetComponent(TRANSFORM));

	pBulletTrans->mAngle = shipTrans->mAngle;

	pBulletBody->mBodyPos.x = shipBody->mBodyPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
	pBulletBody->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


	pBulletTrans->mPos.x = shipTrans->mPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
	pBulletTrans->mPos.y = shipTrans->mPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


	pBulletBody->mBodyVel.x = cosf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  MISSILESPEED;
	pBulletBody->mBodyVel.y = sinf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  MISSILESPEED;
	}
}


void Missile::Update(float dt)
{
	// Homing Missile Behavior

		FindTgt();

	if (!homing) {
		return;
	}
	homing = false;

	if (target == NULL)
	{
		FindTgt();
	}

	Body *targetBody = static_cast<Body*>(target->GetComponent(BODY));
	Transform *targetTrans = static_cast<Transform*>(target->GetComponent(TRANSFORM));

	Body *missileBody = static_cast<Body*>(this->mpOwner->GetComponent(BODY));
	Transform *missileTrans = static_cast<Transform*>(this->mpOwner->GetComponent(TRANSFORM));

	Matrix2D rotation;
	Vector2D target_vector, normalized_target_vector, normal;
	float cos_angle, angle, turn;


	Vector2D missileposition;
	Vector2DSet(&missileposition, missileBody->mBodyPos.x, missileBody->mBodyPos.y);


	Vector2D targetPosition;
	Vector2DSet(&targetPosition, targetBody->mBodyPos.x, targetBody->mBodyPos.y);


	// target vector
	Vector2DSub(&target_vector, &targetPosition, &missileposition);
	// unit vector in dir of target
	Vector2DNormalize(&normalized_target_vector, &target_vector);


	Vector2D missileVel;
	Vector2DSet(&missileVel, missileBody->mBodyVel.x, missileBody->mBodyVel.y);
	cos_angle = Vector2DDotProduct(&normalized_target_vector, &missileVel);

	angle = glm::radians(acosf(cos_angle));
	//calculating normal
	Matrix2DRotRad(&rotation, 90);
	Matrix2DMultVec(&normal, &rotation, &missileVel);
	// DOT product for turning
	turn = Vector2DDotProduct(&normal, &target_vector);
	if (turn > 0)
	{

		missileTrans->mAngle += glm::degrees(angle);

		Vector2D missinewVel;
		missinewVel.x = missileBody->mBodyVel.x;
		missinewVel.y = missileBody->mBodyVel.y;

		Vector2DFromAngleDeg(&missinewVel, (missileTrans->mAngle));
		Vector2DScale(&missinewVel, &missinewVel, 0.75f);
		missileBody->mBodyVel.x = missinewVel.x;
		missileBody->mBodyVel.y = missinewVel.y;
	}
	else
	{
		missileTrans->mAngle -= glm::degrees(angle);
		Vector2D missinewVel;
		missinewVel.x = missileBody->mBodyVel.x;
		missinewVel.y = missileBody->mBodyVel.y;

		Vector2DFromAngleDeg(&missinewVel, (missileTrans->mAngle));
		Vector2DScale(&missinewVel, &missinewVel, 0.75f);
		missileBody->mBodyVel.x = missinewVel.x;
		missileBody->mBodyVel.y = missinewVel.y;

	}

	missileBody->mBodyVel.x = cosf((missileTrans->mAngle + 90)* 3.14f / 180.0f)*MISSILE_SPEED;
	missileBody->mBodyVel.y = sinf((missileTrans->mAngle + 90)* 3.14f / 180.0f)*MISSILE_SPEED;

}

void Missile::Serialize(FILE ** fpp)
{
	gEM->Subscribe(MISSILEHIT, this->mpOwner);
	
}

void Missile::HandleEvent(Event * pEvent)
{
 	if (MISSILEHIT == pEvent->mType) {

		homing = false;
		target = nullptr;

		//FindTgt();
		GOM->mDestoryQ.push_back(this->mpOwner);
	}
}

void Missile::FindTgt()
{
	this->target = nullptr;
	for (auto gameObjects : GOM->mGameObjects)
	{
		if (gameObjects->ObjectType == ASTEROID) {
			AsteroidHandler *temp = static_cast<AsteroidHandler *> (gameObjects->GetComponent(ASTEROIDHAN));
			if (temp->ActiveFlag == true) {
				homing = true;
				if (!target) {
					target = gameObjects;
					break;
				}
			}
		}
	}
}

 