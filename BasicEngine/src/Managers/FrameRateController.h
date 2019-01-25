/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			FrameRateController.h
Purpose:			FrameRateController header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/


#pragma once

#include "SDL_stdinc.h"

class FrameRateController
{
public:
	FrameRateController(Uint32 MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();

	Uint32 GetFrameTime();

private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mFrameTime;

	Uint32 mNeededTickPerFrame;
};

