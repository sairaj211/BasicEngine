/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Renderer.cpp
Purpose:			Renderer implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Renderer.h"
#include<iostream>

void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "):" << function <<
			" " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(0.5,0.5,0.5,0.5));
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib,  Shader* shader) const
{
	shader->Bind();
	va.Bind();
	ib.Bind();
	/*
	if (!Debug)
	{
		shader->SetUniform1i("isDebug", 0);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	}
	else
	{
		shader->SetUniform1i("isDebug", 1);
		//glUniform1i(glGetUniformLocation(pS1->ID, "is_debug"), 1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		GLCall(glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr));
		//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
	}*/

	shader->SetUniform1i("isDebug", 0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	
}

void Renderer::DebugDraw(const VertexArray & va, const IndexBuffer & ib, Shader* shader) const
{
	shader->Bind();
	va.Bind();
	ib.Bind();
	shader->SetUniform1i("isDebug", 1);
	//glUniform1i(glGetUniformLocation(pS1->ID, "is_debug"), 1);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLCall(glDrawElements(GL_LINE_LOOP, 6, GL_UNSIGNED_INT, nullptr));
}