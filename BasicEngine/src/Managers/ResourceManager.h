/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			ResourceManager.h
Purpose:			ResourceManager header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/


#pragma once

#include <string>
#include <unordered_map>
#include "Texture.h"

struct SDL_Surface; // forward declaration

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	Texture *LoadTextures(const char * pFilePath);

private:
	std::unordered_map<std::string, Texture *> mTexture;
};

