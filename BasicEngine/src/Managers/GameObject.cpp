/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			GameObject.cpp
Purpose:			GameObject implementation 
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "GameObject.h"
#include "stdio.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "Body.h"
#include "EventManager.h"
#include "WrapA.h"
#include "Outofbound.h"
#include "BlackHole.h"
#include "AsteroidHandler.h"
#include "Missile.h"

GameObject::GameObject(GameObjectType ObjType)
	:ObjectType(ObjType)
{
	ActiveFlag = true;
	/*mpSprite = nullptr;
	mpTrasform = nullptr;
	mpController = nullptr;*/

	
}

//
//GameObject::GameObject()
//{
//}

GameObject::~GameObject()
{
	for (auto c : mComponents)
		delete c;
	mComponents.clear();

}

void GameObject::Update(float dt)
{
	/*if (nullptr != mpSprite)
		mpSprite->Update();
	if (nullptr != mpTrasform)
		mpTrasform->Update();
	if (nullptr != mpTrasform)
		delete mpTrasform;*/

	for (auto c : mComponents)
		c->Update(dt);
}

Component *GameObject::AddComponent(unsigned int Type)
{
	Component *pNewComponent =nullptr;
	switch (Type)
	{
	case TRANSFORM:
		pNewComponent = new Transform();
		break;
	case SPRITE:
		pNewComponent = new Sprite();
		break;
	case CONTROLLER:
		pNewComponent = new Controller();
		break;
	case UPDOWN:
		pNewComponent = new UpDown();
		break;
	case BODY:
		pNewComponent = new Body();
		break;
	case WRAPA:
		pNewComponent = new WrapA();
		break;
	case WRAPD:
		pNewComponent = new Outofbound();
		break;
	case ASTEROIDSPAWNER:
		pNewComponent = new BlackHole();
		break;
	case ASTEROIDHAN:
		pNewComponent = new AsteroidHandler();
		break;
	case MISSILE:
		pNewComponent = new Missile();
		break;
	}


	if (nullptr != pNewComponent)
	{
		mComponents.push_back(pNewComponent);
		pNewComponent->mpOwner = this;
	}	

	return pNewComponent;

}

Component *GameObject::GetComponent(unsigned int Type)
{
	for (auto c : mComponents)
		if (c->GetType() == Type) {
			return c;
		}
	return nullptr;
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (auto c : mComponents)
		c->HandleEvent(pEvent);
}
