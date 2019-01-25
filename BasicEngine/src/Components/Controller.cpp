/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Controller.cpp
Purpose:			Controller implementaion files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/
#include <glm/glm.hpp>
#include "Controller.h"
#include "GameObject.h"
#include "Input.h"
#include "SDL_scancode.h"
#include "Sprite.h"
#include "PhysicsManager.h"
#include "Shader.h"
#include "ObjectFactory.h"
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <stdio.h>
#include "GameObjectManager.h"
#include "Missile.h"	
#include <iostream>

extern GameObjectManager *GOM;
extern Input_Manager *gpInputManager;
extern ObjectFactory *gOF;
extern EventManager *gEM;
extern Shader* shader;
extern Renderer* gRenderer;


float BULLETSPEED = 0.75;
#define MISSILESPEED 0.25f

PlayerHitEvent::PlayerHitEvent() : Event(PLAYERHIT)
{
}

PlayerHitEvent::~PlayerHitEvent()
{
}

WeaponUpgrade::WeaponUpgrade() : Event(WEAPONUPGRADE)
{
}

WeaponUpgrade::~WeaponUpgrade()
{
}


Controller::Controller() :Component(CONTROLLER)
{
	lives = 3;
}


Controller::~Controller()
{
	powerUp = false;
}

void Controller::Update(float dt)
{
	//printf("%d", mpOwner);
	if (nullptr != mpOwner && nullptr != gpInputManager)
	{
		/*GameObject *gTemp = nullptr;
		gTemp = GOM->GetType(BLACKHOLE);

		BlackHole *bhTemp = static_cast<BlackHole *>(gTemp->GetComponent(ASTEROIDSPAWNER));*/
		Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));
		Body *pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		Sprite *pSr = static_cast<Sprite *>(mpOwner->GetComponent(SPRITE));
		if (nullptr != pBody)
		{
			if (this->mpOwner->ObjectType == MENU)
			{
				if (gpInputManager->isKeyTriggered(SDL_SCANCODE_S)) 
					gOF->LoadLevel("Levels/Level1.txt");
			}

			 if (this->mpOwner->ObjectType == PLAYER) {
				if (gpInputManager->isKeyPressed(SDL_SCANCODE_UP)) {
					pBody->mBodyForce.x = cosf((pTr->mAngle + 90.0f) * 3.14f / 180.0f);
					pBody->mBodyForce.y = sinf((pTr->mAngle + 90.0f) * 3.14f / 180.0f);
				}

				if (gpInputManager->isKeyPressed(SDL_SCANCODE_DOWN)) {
					pBody->mBodyForce.x = -cosf((pTr->mAngle + 90.0f) * 3.14f / 180.0f);
					pBody->mBodyForce.y = -sinf((pTr->mAngle + 90.0f) * 3.14f / 180.0f);
				}

				if (gpInputManager->isKeyPressed(SDL_SCANCODE_LEFT)) {
					pTr->mAngle += 2.5f;
				}
				if (gpInputManager->isKeyPressed(SDL_SCANCODE_RIGHT)) {
					pTr->mAngle -= 2.5f;
				}
				if (gpInputManager->isKeyTriggered(SDL_SCANCODE_M)) {

					CreateMissile();
				}
				if (gpInputManager->isKeyTriggered(SDL_SCANCODE_D)) {
					gRenderer->Debug = !gRenderer->Debug;
				}
				if (gpInputManager->isKeyTriggered(SDL_SCANCODE_SPACE)) {
					CreateBullet(pBody, pTr);
				}

			}

			 if (this->mpOwner->ObjectType == SCREEN) {
				 if (gpInputManager->isKeyTriggered(SDL_SCANCODE_R)) {
					 gOF->LoadLevel("Levels/Level1.txt");
					 std::cout << "**********************************************************************" << std::endl;
					 std::cout << "############                  NEW GAME                     ###########" << std::endl;
					 std::cout << "**********************************************************************" << std::endl;
				 }
			 }
			/*else if (gpInputManager->isKeyPressed(SDL_SCANCODE_S))
				pBody->mBodyPos.y -= 10;
			else if (gpInputManager->isKeyPressed(SDL_SCANCODE_A))
				pBody->mBodyPos.x -= 2;	
			else if (gpInputManager->isKeyPressed(SDL_SCANCODE_D))
				pBody->mBodyPos.x += 2;
			else if (gpInputManager->isKeyPressed(SDL_SCANCODE_Q))
				pTr->mAngle += glm::radians(5.0f);
			else if (gpInputManager->isKeyPressed(SDL_SCANCODE_E))
				pTr->mAngle -= glm::radians(5.0f);
			else if (gpInputManager->isKeyTriggered(SDL_SCANCODE_SPACE))
			{
				isColor = !isColor;
				if (isColor)
					shader->SetUniform1i("plainColor", 1);
				else
					shader->SetUniform1i("plainColor", 0);
					
			}*/
		}
	}
}


void Controller::Serialize(FILE ** fpp)
{
	gEM->Subscribe(PLAYERHIT, this->mpOwner);
	gEM->Subscribe(WEAPONUPGRADE, this->mpOwner);
}

void Controller::HandleEvent(Event *pEvent)
{
	//REFERENCE
	/*if (COLLIDE == pEvent->mType)
	{
		CollideEvent *pRealEvent = static_cast<CollideEvent *>(pEvent);
		Body *pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));

		if (nullptr != pBody)
			pBody->mBodyPos.x = 0.0f;

		PlayerHitEvent *pPHE = new PlayerHitEvent();
		pPHE->mTimer = 2.0f;
		gEM->AddTimedEvent(pPHE);
		gEM->BroadCastEventToSubscribe(pPHE);
	}*/

	if (PLAYERHIT == pEvent->mType)
	{
		Transform *pTr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));
		Body *pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));

		pBody->mBodyPos.x = 400.0f;
		pBody->mBodyPos.y = 50.0f;

		pBody->mBodyVel.x = 0.0f;
		pBody->mBodyVel.y = 0.0f;

		pTr->mAngle = 0.0f;

	
		lives--;
		std::cout << "Player Lives = " << lives << std::endl;
		//	std::cout << "LIVES = " << lives << std::endl;
		if (lives == 0)
		{
			std::cout << "GAME OVER........." << std::endl;
			gOF->LoadLevel("Levels/LoseScreen.txt");
			std::cout << "Loading LoseScreen" << std::endl;
			//TO DO LOAD win / lose SCREEN
			std::cout << "######################################################################" << std::endl;
		}

	}

	if (WEAPONUPGRADE == pEvent->mType) 
	{
		//this->powerUp = true;
		//gOF->LoadLevel("WinScreen.txt");
	}
}

void Controller::CreateBullet(Body *shipBody, Transform *shipTrans)
{
	if (powerUp == false) {
		GameObject *pBullet = gOF->LoadObject("Archetypes/Bullet.txt");
		Body *pBulletBody = static_cast<Body*>(pBullet->GetComponent(BODY));
		Transform *pBulletTrans = static_cast<Transform*>(pBullet->GetComponent(TRANSFORM));


		pBulletTrans->mAngle = shipTrans->mAngle;

		pBulletBody->mBodyPos.x = shipBody->mBodyPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletBody->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletTrans->mPos.x = shipTrans->mPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletTrans->mPos.y = shipTrans->mPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletBody->mBodyVel.x = cosf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;
		pBulletBody->mBodyVel.y = sinf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;

	}
	if(powerUp == true)
	{
		GameObject *pBullet = gOF->LoadObject("Bullet.txt");
		Body *pBulletBody = static_cast<Body*>(pBullet->GetComponent(BODY));
		Transform *pBulletTrans = static_cast<Transform*>(pBullet->GetComponent(TRANSFORM));


		pBulletTrans->mAngle = shipTrans->mAngle;

		pBulletBody->mBodyPos.x = shipBody->mBodyPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletBody->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletTrans->mPos.x = shipTrans->mPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletTrans->mPos.y = shipTrans->mPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletBody->mBodyVel.x = cosf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;
		pBulletBody->mBodyVel.y = sinf((pBulletTrans->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;

		GameObject *pBullet1 = gOF->LoadObject("Bullet.txt");
		Body *pBulletBody1 = static_cast<Body*>(pBullet1->GetComponent(BODY));
		Transform *pBulletTrans1 = static_cast<Transform*>(pBullet1->GetComponent(TRANSFORM));


		pBulletTrans1->mAngle = shipTrans->mAngle - 5.0f;

		pBulletBody1->mBodyPos.x = shipBody->mBodyPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletBody1->mBodyPos.y = shipBody->mBodyPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletTrans1->mPos.x = shipTrans->mPos.x + cosf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;
		pBulletTrans1->mPos.y = shipTrans->mPos.y + sinf((shipTrans->mAngle + 90) *3.14f / 180.0f) * 20.5f;


		pBulletBody1->mBodyVel.x = cosf((pBulletTrans1->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;
		pBulletBody1->mBodyVel.y = sinf((pBulletTrans1->mAngle + 90.0f) * 3.14f / 180.0f) *  BULLETSPEED;
	}
	
}

void Controller::CreateMissile()
{
	Missile *pMissile = new Missile();
	pMissile->CreateMissile();
	
}

void Controller::GetBlackHoleHealth()
{
}

//Missile Creation
/*
void Controller::CreateMissile(Body *shipBody, Transform *shipTrans)
{
	GameObject *pBullet = gOF->LoadObject("Missile.txt");
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

*/

