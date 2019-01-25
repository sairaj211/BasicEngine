/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Renderer.h
Purpose:			Renderer header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#pragma once

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GlClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GlClearError();

bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{

public:
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib,  Shader* shader) const;

	void DebugDraw(const VertexArray & va, const IndexBuffer & ib, Shader* shader) const;
public:
	bool Debug = false;
};