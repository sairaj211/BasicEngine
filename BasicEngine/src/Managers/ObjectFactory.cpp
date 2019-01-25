/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			ObjectFactory.cpp
Purpose:			ObjectFactory implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "ObjectFactory.h"

#include "Transform.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "Body.h"
#include "WrapA.h"
#include "Missile.h"

extern GameObjectManager *GOM;
extern GameObject* Player;
ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}


GameObject * ObjectFactory::LoadObject(const char * pFileName)
{
	GameObject *pNewGameObject = nullptr;

	FILE *fp;
	
	std::string filepath = resourcePath + pFileName;
	fopen_s(&fp, filepath.c_str(), "r");

	if (fp)
	{
		char ObjectType[256] = { 0 };
		fscanf_s(fp, "%255s\n", ObjectType, sizeof(ObjectType));
		if (0 == strcmp(ObjectType, "Player"))
		{
			pNewGameObject = new GameObject(PLAYER);
		}
		else if (0 == strcmp(ObjectType, "Asteroid"))
		{
			pNewGameObject = new GameObject(ASTEROID);
		}
		else if (0 == strcmp(ObjectType, "Bullet"))
		{
			pNewGameObject = new GameObject(BULLET);
		}
		else if (0 == strcmp(ObjectType, "Missile"))
		{
			pNewGameObject = new GameObject(MISSILESPAWN);
		}
		else if (0 == strcmp(ObjectType, "Enemy"))
		{
			pNewGameObject = new GameObject(ENEMY);
		}
		else if (0 == strcmp(ObjectType, "Background"))
		{
			pNewGameObject = new GameObject(BACKGROUND);
		}
		else if (0 == strcmp(ObjectType, "BlackHole"))
		{
			pNewGameObject = new GameObject(BLACKHOLE);
		}
		else if (0 == strcmp(ObjectType, "Screen"))
		{
			pNewGameObject = new GameObject(SCREEN);
		}
		else if (0 == strcmp(ObjectType, "Menu"))
		{
			pNewGameObject = new GameObject(MENU);
		}
		//pNewGameObject = new GameObject();

		while (!feof(fp))
		{
			char componentName[256] = { 0 };
			fscanf_s(fp, "%255s", componentName, sizeof(componentName));
			std::string stringcomponentN = componentName;

			Component *pNewComponent = nullptr;

			if ("Transform" == stringcomponentN) {
				pNewComponent = pNewGameObject->AddComponent(TRANSFORM);
			}
			else if ("Sprite" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(SPRITE);
			}
			else if ("Controller" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(CONTROLLER);

			//	Player = pNewGameObject;
			}
			else if ("UpDown" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(UPDOWN);
			}
			else if ("Body" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(BODY);
			}
			else if ("Wrap_A" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(WRAPA);
			}
			else if ("Wrap_D" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(WRAPD);
			}
			else if ("AsteoridSpawner" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(ASTEROIDSPAWNER);
			}
			else if ("Asteroid_Handler" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(ASTEROIDHAN);
			}
			else if ("Missile_U" == stringcomponentN)
			{
				pNewComponent = pNewGameObject->AddComponent(MISSILE);
			}
			 if (nullptr != pNewComponent)
			{
				pNewComponent->Serialize(&fp);
			}
		
		}
		GOM->mGameObjects.push_back(pNewGameObject);
		fclose(fp);
	}

	return pNewGameObject;

}


void ObjectFactory::LoadLevel(const char *pFileName)
{
	GOM->mGameObjects.erase(GOM->mGameObjects.begin(), GOM->mGameObjects.end());

	FILE *fp;
	std::string filePath;
	filePath = resourcePath + pFileName;
	fopen_s(&fp, filePath.c_str(), "r");

	if (fp)
	{
		while ( !feof(fp))
		{
			char objectFileName[256] = { 0 };
			fscanf_s(fp, "%255s", objectFileName, sizeof(objectFileName));
			std::string stringobjectFileName = objectFileName;
				
			GameObject *pGO = LoadObject(stringobjectFileName.c_str());

			//override transform 
			Transform *pTr = static_cast<Transform *>(pGO->GetComponent(TRANSFORM));
			pTr->Serialize(&fp);

			//Grab the initial position from the transform component
			Body *pBody = static_cast<Body *>(pGO->GetComponent(BODY));
			if ((nullptr != pBody))
				pBody->Initilize();

			
		}

		fclose(fp);

	}
}