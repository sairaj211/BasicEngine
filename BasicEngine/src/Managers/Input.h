/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Input.h (InputManagers)
Purpose:			Input header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/


#ifndef INPUT_H

#define INPUT_H
#include "SDL_stdinc.h"
class Input_Manager
{
public:
	Input_Manager();
	~Input_Manager();

	void Update();

	bool isKeyPressed(unsigned int keyScanCode);
	bool isKeyTriggered(unsigned int keyScanCode);
	bool isKeyReleased(unsigned int keyScanCode);

private:
	Uint8 mcurrentState[512];
	Uint8 mPreviousState[512];
};

#endif //

