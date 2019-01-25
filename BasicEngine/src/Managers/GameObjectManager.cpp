/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			GameObjectManager.cpp
Purpose:			GameObjectManager implementaion files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "GameObjectManager.h"
#include "GameObject.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Transform.h"
#include "Sprite.h"
#include "glm/gtc/matrix_transform.hpp"

extern Renderer* gRenderer;

GameObjectManager::GameObjectManager()
{

}


GameObjectManager::~GameObjectManager()
{
	for (auto go : mGameObjects)
		delete go;

	mGameObjects.clear();
}

void GameObjectManager::Update(float dt)
{
	/*for (auto it : mGameObjects)
	{
		it->Update(dt);
	}*/
	//printf("size = %d\n", mGameObjects.size());
	for (unsigned int i = 0; i < mGameObjects.size(); ++i)
	{
		mGameObjects[i]->Update(dt);
	}
}

void GameObjectManager::DrawGameObjects(const VertexArray & va, const IndexBuffer & ib,  Shader* shader)
{
	for (auto it : mGameObjects)
	{
		//take transform
		//Transform* ptrans = static_cast<Transform*>(it->GetComponent(0));
		Transform *pTr = static_cast<Transform *>(it->GetComponent(TRANSFORM));
		
		glm::mat4 proj = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		//set transform in shader
		shader->SetUniformMat4f("u_MVP", proj * pTr->mTransform);
		//get texture 
		Sprite *pSprite = static_cast<Sprite *>(it->GetComponent(SPRITE));

		
		//bind it 
		pSprite->mTexture->Bind();

		//set texture slot 
		shader->SetUniform1i("u_Texture", 0);
		//finally draw
		gRenderer->Draw(va,ib,shader);

		//If debug mode ON
		if (gRenderer->Debug)
		{
			pTr->DebugUpdate();
			shader->SetUniformMat4f("u_MVP", proj* pTr->mTransform);
			gRenderer->DebugDraw(va,ib,shader);
		}
	}
}

void GameObjectManager::DestoryQ()
{
	//for (auto gameObjects : mDestoryQ)
	for(unsigned int i = 0; i < mDestoryQ.size(); ++i)
	{
		auto it = std::find(mGameObjects.begin(), mGameObjects.end(), mDestoryQ[i]);
		if (it != mGameObjects.end())
		{
			delete *it;
			mGameObjects.erase(it);
		}
	}
	mDestoryQ.clear();

}

GameObject* GameObjectManager::GetType(GameObjectType objType)
{
	for (unsigned int i = 0; i < mGameObjects.size(); i++)
	{
		if (mGameObjects[i]->ObjectType == objType)
			return mGameObjects[i];
	}
	return nullptr;
}
