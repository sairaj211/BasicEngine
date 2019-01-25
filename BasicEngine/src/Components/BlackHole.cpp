/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			BlackHole.cpp
Purpose:			BlackHole implementation 
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "BlackHole.h"
#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "ObjectFactory.h"
#include "GameObjectManager.h"
#include "Controller.h"
#include "Controller.h"
#include <iostream>

//50.0f, 110.0f, 180.0f, 270.0f, 340.0f, 400.0f, 450.0f, 520.0f, 610.0f, 680.0f, 720.0f, 770.0f
extern ObjectFactory *gOF;
extern EventManager *gEM;
extern GameObjectManager *GOM;
//Random pos to spawn asteroids
float AsteroidPos[10][2] = {
		50.0f, 523.0f,
		45.0f, 320.0f,
		100.0f, 120.0f,
		180.0f, 250.0f,
		250.0f, 420.0f,
		300.0f, 450.0f,
		450.0f, 410.0f,
		500.0f, 350.0f,
		600.0f, 250.0f,
		720.0f, 523.0f

};

int BlackHole::Asteroid_Count = 0;
int BlackHole::Asteroid_Destoryed = 0;

BlackHole::BlackHole():Component(ASTEROIDSPAWNER)
{
	health = 100;
	Asteroid_Count = 0;
	Asteroid_Destoryed = 0;
}

BlackHole::~BlackHole()
{
}


void BlackHole::Update(float dt)
{



	if (Asteroid_Count <= 0 && health > 0)
	{

		int num = 2;
		for (int i = 0; i < num; i++)
			CreateAsteorid();
	}

	if (health == 0)
	{
		//WeaponUpgrade *weaUP = new WeaponUpgrade();
		//gEM->BroadCastEvent(weaUP);
		//health = 100;


		MassDestruction *mDestroy = new MassDestruction();
		ResetAsteroidsEvent *mReset = new ResetAsteroidsEvent();
		std::cout << "**********************************************************************" << std::endl;
		std::cout << "############            MASS DESTRUCTION                 #############" << std::endl;
		std::cout << "**********************************************************************" << std::endl;
		std::cout << "IN 3 SECONDS.........................................................." << std::endl;
		mDestroy->mTimer = 3.0f;
		mReset->mTimer = 5.0f;
		gEM->AddTimedEvent(mDestroy);
		gEM->AddTimedEvent(mReset);
		//gEM->BroadCastEvent(mDestroy);
		//gEM->BroadCastEventToSubscribe(mDestroy);
		health = 100;
		
 		//gOF->LoadLevel("WinScreen.txt");
	}

	if (Asteroid_Destoryed == 5)
	{
		WeaponUpgrade *weaUP = new WeaponUpgrade();
		gEM->BroadCastEvent(weaUP);
		Asteroid_Destoryed = 0;
		gOF->LoadLevel("Levels/WinScreen.txt");
		std::cout << "######################################################################" << std::endl;
	}
}

void BlackHole::CreateAsteorid()
{
	Asteroid_Count++;


	GameObject *pAsteroid = gOF->LoadObject("Archetypes/Asteroid.txt");
	Body *pAsteroidBody = static_cast<Body*>(pAsteroid->GetComponent(BODY));
	Transform *pAsteroidTrans = static_cast<Transform*>(pAsteroid->GetComponent(TRANSFORM));

	int num = rand() % 10;
	int num1 = rand() % 10;

	pAsteroidTrans->mPos.x = pAsteroidBody->mBodyPos.x = (float)(rand() % 800) ;
	pAsteroidTrans->mPos.y = pAsteroidBody->mBodyPos.y = (float)(rand() % 600) ;

	//pAsteroidTrans->mPos.x = pAsteroidBody->mBodyPos.x = AsteroidPos[num][0];
	//pAsteroidTrans->mPos.y = pAsteroidBody->mBodyPos.y = AsteroidPos[num][1];

}

void BlackHole::Serialize(FILE **fpp)
{
	gEM->Subscribe(BLACKHOLEHEALTH, this->mpOwner);
	gEM->Subscribe(SPAWNASTEROIDS, this->mpOwner);
}

void BlackHole::HandleEvent(Event * pEvent)
{

	if (BLACKHOLEHEALTH == pEvent->mType)
	{
		health -= 10;
		std::cout << "Black Hole Health = " << health << std::endl;
	}

	if (SPAWNASTEROIDS == pEvent->mType)
	{
		Asteroid_Count = 0;
	}

}


BlackHoleHitEvent::BlackHoleHitEvent() : Event(BLACKHOLEHEALTH)
{
}

BlackHoleHitEvent::~BlackHoleHitEvent()
{
}

ResetAsteroidsEvent::ResetAsteroidsEvent() : Event(SPAWNASTEROIDS)
{
}

ResetAsteroidsEvent::~ResetAsteroidsEvent()
{
}
