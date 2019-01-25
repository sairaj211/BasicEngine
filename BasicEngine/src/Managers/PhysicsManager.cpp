/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			PhysicsManager.cpp
Purpose:			PhysicsManager implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "PhysicsManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Body.h"
#include "UpDown.h"
#include "Controller.h"
#include "AsteroidHandler.h"
#include "BlackHole.h"
#include "Missile.h"
#include "Outofbound.h"


extern GameObjectManager *GOM;
extern CollisionManager *gCM;

PhysicsManager::PhysicsManager()
{
}


PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update(float FrameTime)
{
	//GameObject *g;
	//int type = 0;
	// integrate all body components
	for (auto go : GOM->mGameObjects)
	{
	//	g = GOM->GetType(PLAYER);
		//type = g->ObjectType;
		Body *pBody = static_cast <Body *>(go->GetComponent(BODY));
		if ((nullptr != pBody))
		{
			pBody->Integrate(0.0f, FrameTime/*,type*/);
			//type = 0;
		}
	}

	//reset previous contacts
	gCM->Reset();

	//check for intersections
	auto pObj1 = GOM->mGameObjects.begin();
	auto pObjLast = GOM->mGameObjects.end();
	
	for (; pObj1 != pObjLast ; ++ pObj1)
	{
		Body *pBody1 = static_cast <Body *>((*pObj1)->GetComponent(BODY));
		if ((nullptr == pBody1))
			continue;

		for (auto pObj2 = pObj1 + 1; pObj2 != pObjLast; ++pObj2)
		{
			Body *pBody2 = static_cast <Body *>((*pObj2)->GetComponent(BODY));
			if ((nullptr == pBody2))
				continue;

			gCM->CheckCollisionAndGenerateContact(pBody1->pShape, pBody1->mBodyPos.x, pBody1->mBodyPos.y,
				pBody2->pShape, pBody2->mBodyPos.x, pBody2->mBodyPos.y, gCM->mContacts);


		}
	}
	
	//Super advanced physics

	for (auto c : gCM->mContacts)
	{
		//CollideEvent ce;
		PlayerHitEvent playerHit;
		BulletHitEvent bulletHit;
		DestroyBullet destroybullet;
		AsteroidBullerHit astBulletHit;
		PlayerEnemyCollide PEcollide;
		PlayerAsteroidCollide PACollide;
		MissileHItEvent mHit;
		AsteroidMissileHit AMHit;
		BlackHoleHitEvent BHevent;
		AsteroidCollisionResponse collisionResponse;
		StopUpdown sup;
		/*if (c->mpBodies[0]->mpOwner->ObjectType == ENEMY && c->mpBodies[1]->mpOwner->ObjectType == BULLET)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&be);
			c->mpBodies[1]->mpOwner->HandleEvent(&be);

		}*/


		if (c->mpBodies[0]->mpOwner->ObjectType == ENEMY && c->mpBodies[1]->mpOwner->ObjectType == BULLET)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&bulletHit);
			c->mpBodies[1]->mpOwner->HandleEvent(&destroybullet);

		}

		else if (c->mpBodies[0]->mpOwner->ObjectType == ASTEROID && c->mpBodies[1]->mpOwner->ObjectType == BULLET)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&astBulletHit);
			c->mpBodies[1]->mpOwner->HandleEvent(&destroybullet);

		}

		else if (c->mpBodies[0]->mpOwner->ObjectType == PLAYER )
		{
			if (c->mpBodies[1]->mpOwner->ObjectType == ENEMY)
			{
				c->mpBodies[0]->mpOwner->HandleEvent(&playerHit);
				c->mpBodies[1]->mpOwner->HandleEvent(&PEcollide);
			}
			if (c->mpBodies[1]->mpOwner->ObjectType == ASTEROID)
			{
				c->mpBodies[0]->mpOwner->HandleEvent(&playerHit);
				c->mpBodies[1]->mpOwner->HandleEvent(&PACollide);
			}

		}

		else if ( (c->mpBodies[0]->mpOwner->ObjectType == ASTEROID && c->mpBodies[1]->mpOwner->ObjectType == MISSILESPAWN) 
			|| (c->mpBodies[0]->mpOwner->ObjectType == MISSILESPAWN && c->mpBodies[1]->mpOwner->ObjectType == ASTEROID) )
		{
			c->mpBodies[0]->mpOwner->HandleEvent(&AMHit);
			c->mpBodies[1]->mpOwner->HandleEvent(&mHit);

		}
		else if (c->mpBodies[0]->mpOwner->ObjectType == BLACKHOLE && c->mpBodies[1]->mpOwner->ObjectType == BULLET)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&BHevent);
			c->mpBodies[1]->mpOwner->HandleEvent(&destroybullet);

		}

		else if (c->mpBodies[0]->mpOwner->ObjectType == ASTEROID && c->mpBodies[1]->mpOwner->ObjectType == ENEMY)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&collisionResponse);
			c->mpBodies[1]->mpOwner->HandleEvent(&sup);

		}

		else if (c->mpBodies[0]->mpOwner->ObjectType == ENEMY && c->mpBodies[1]->mpOwner->ObjectType == ASTEROID)
		{

			c->mpBodies[0]->mpOwner->HandleEvent(&sup);
			c->mpBodies[1]->mpOwner->HandleEvent(&collisionResponse);
		}

	}
	 
}
