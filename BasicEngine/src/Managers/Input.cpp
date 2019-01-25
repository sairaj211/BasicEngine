/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Input.cpp (InputManager)
Purpose:			Input 
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Input.h"
#include "SDL_keyboard.h"
#include <iostream>

Input_Manager::Input_Manager()
{
	SDL_memset(mcurrentState, 0, 512 * sizeof(Uint8));
	SDL_memset(mPreviousState, 0, 512 * sizeof(Uint8));
}

Input_Manager::~Input_Manager()
{

}

void Input_Manager::Update()
{
	int numberofFetch = 0;
	const Uint8* pCurrentKey = SDL_GetKeyboardState(&numberofFetch);

	if (numberofFetch > 512)
		numberofFetch = 512;

	SDL_memcpy(mPreviousState, mcurrentState, 512 * sizeof(Uint8));
	SDL_memcpy(mcurrentState, pCurrentKey, numberofFetch * sizeof(Uint8));

}

bool Input_Manager::isKeyPressed(unsigned int keyScanCode)
{
	if (keyScanCode >= 512)
		return false;


	if (mcurrentState[keyScanCode])
	{
		//std::cout << "key Pressed : " << keyScanCode << std::endl;
		return true;
	}
	
	
	return  false;
}


bool Input_Manager::isKeyTriggered(unsigned int keyScanCode)
{

	if (keyScanCode >= 512)
		return false;


	if (mcurrentState[keyScanCode] && !mPreviousState[keyScanCode])
		return true;
	
	return  false;
}

bool Input_Manager::isKeyReleased(unsigned int keyScanCode)
{
	if (keyScanCode >= 512)
		return false;


	if (!mcurrentState[keyScanCode] && mPreviousState[keyScanCode])
		return true;

	return  false;
}