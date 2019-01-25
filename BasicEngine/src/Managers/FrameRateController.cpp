/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			FrameRateController.cpp
Purpose:			FrameRateController implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "FrameRateController.h"
#include "SDL_timer.h"

FrameRateController::FrameRateController(Uint32 MaxFrameRate)
{
	mTickStart = mTickEnd = mFrameTime = 0;
	if (0 != MaxFrameRate)
		mNeededTickPerFrame = 1000 / MaxFrameRate;
	else
		mNeededTickPerFrame = 0;
}


FrameRateController::~FrameRateController()
{

}
void FrameRateController::FrameStart()
{
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd()
{
	mTickEnd = SDL_GetTicks();

	while (mTickEnd - mTickStart < mNeededTickPerFrame) {
		mTickEnd = SDL_GetTicks();
	}

	mFrameTime = mTickEnd - mTickStart;
}

Uint32 FrameRateController::GetFrameTime()
{
	return mFrameTime;
}