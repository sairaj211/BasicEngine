/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Sprite.cpp
Purpose:			Sprite Implementation header files(Load Textures)
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Sprite.h"
#include "string.h"
#include "ResourceManager.h"
#include "SDL_surface.h"

extern ResourceManager *gpResource;

Sprite::Sprite() : Component(SPRITE)
{
	mTexture = nullptr;
	
}


Sprite::~Sprite()
{
}

void Sprite::Update(float dt)
{
}

void Sprite::Serialize(FILE **fpp)
{
	char imageName[256];
	memset(imageName, 0, 256 * sizeof(char));

	std::string fullpath = "Res\\";
	fscanf_s(*fpp, "%255s\n", imageName, sizeof(imageName));

	
	fullpath += imageName;

	//printf("%s", fullpath);
	//mTexture = new Texture(fullpath);

	mTexture = gpResource->LoadTextures(fullpath.c_str());

	//mpSurface = gpResource->LoadSurface(fullpath.c_str());
}
