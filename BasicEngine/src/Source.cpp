/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Source.cpp (Main)
Purpose:			Game loop
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include <GL/glew.h>
#include <SDL.h>
#include "windows.h"
#include <iostream>
#include "stdio.h"

#include "Input.h"
#include "FrameRateController.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Component.h"
#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "UpDown.h"
#include "ObjectFactory.h"
#include "Body.h"
#include "WrapA.h"
#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"

#include "Renderer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"


Input_Manager *gpInputManager = nullptr;
FrameRateController *gpFRC = nullptr;
ResourceManager *gpResource = nullptr;
GameObjectManager *GOM = nullptr;
ObjectFactory *gOF = nullptr;
PhysicsManager *gPM = nullptr;
CollisionManager *gCM = nullptr;
EventManager *gEM = nullptr;
Renderer* gRenderer = nullptr;
Shader* shader;

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}


#pragma comment(lib, "legacy_stdio_definitions.lib")

GameObject* Player;



int main(int argc, char *args[])
{

	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle("SDL 2.0 Test");
	}

	SDL_Window *pWindow;
	int error = 0;
	int posX = 0, posY = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)
	{
		
		("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	pWindow = SDL_CreateWindow("BASIC",			// window title
		SDL_WINDOWPOS_CENTERED,					// initial x position
		SDL_WINDOWPOS_CENTERED,					// initial y position
		800,									// width, in pixels
		600,									// height, in pixels
		SDL_WINDOW_OPENGL);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_GLContext gContext = SDL_GL_CreateContext(pWindow);
	if (gContext == NULL)
	{
		printf("Context could not be created%s\n", SDL_GetError());
	}
	else {
		//Initialize GLEW
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			printf("Error\n");
		}
	}

	gpInputManager = new Input_Manager();
	gpFRC = new FrameRateController(60);
	GOM = new GameObjectManager();
	gOF = new ObjectFactory();
	gpResource = new ResourceManager();
	gPM = new PhysicsManager();
	gCM = new CollisionManager();
	gEM = new EventManager();
	gRenderer = new Renderer();
	/*====================================================================================================*/
	/*QUAD*/
	{
		float positions[] = {
			// coordinates	 // Tex Coord
		   -0.5f,  -0.5f,	 0.0f, 0.0f, // 0
			0.5f,  -0.5f,	 1.0f, 0.0f, // 1
			0.5f,   0.5f,	 1.0f, 1.0f, // 2
		   -0.5f,   0.5f,	 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		/*====================================================================================================*/

		shader = new Shader("Res/shaders/Basic.shader");
		shader->Bind();


		/*====================================================================================================*/
		/*KAAM CHALU*/


		gOF->LoadLevel("Levels/Menu.txt");
		float dt;
		while (true == appIsRunning)
		{
			//glEnable()
			gRenderer->Clear();
			gpFRC->FrameStart();

			dt = (float)gpFRC->GetFrameTime();
			//std::cout << "Frame time = " << gpFRC->GetFrameTime() << std::endl;

			SDL_Event e;
			gpInputManager->Update();
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_QUIT)
				{
					appIsRunning = false;
				}

			}

			//call each managers updates

			//GAMEOBJECT MANAGER
			GOM->Update(dt);

			//PHYSICS MANAGER
			gPM->Update(dt);

			//EVENT MANAGER
			gEM->Update(dt);

			//Draw Objects
			GOM->DrawGameObjects(va, ib, shader);

			GOM->DestoryQ();
			SDL_GL_SwapWindow(pWindow);
			gpFRC->FrameEnd();
		}

		free(gpFRC);
		free(gpInputManager);
		free(gpResource);
		free(GOM);
		free(gEM);
		free(gPM);
		free(gCM);
	}
	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}