/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			ResourceManager.cpp
Purpose:			ResourceManager implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "ResourceManager.h"
#include "SDL_surface.h"


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	for (auto &element : mTexture)
		element.second->~Texture();

	mTexture.clear();
}

Texture * ResourceManager::LoadTextures(const char * pFilePath)
{
	//Check hash map
	Texture *pTexture = mTexture[pFilePath];

	//Already loaded?
	if (pTexture)
		return pTexture;

	//Load it
	pTexture = new Texture(pFilePath);

	//Load successful? Add to hash map
	if (pTexture)
	{
		mTexture[pFilePath] = pTexture;
	}

	//return to user
	return pTexture;
}
