/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Shader.cpp
Purpose:			Shader Library implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
 
#include "Renderer.h"



Shader::Shader(const std::string & filepath)
	:m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{	
	GLCall(glDeleteProgram(m_RendererID));
}

ShaderProgramSource Shader::ParseShader(const std::string& fliepath)
{
	std::ifstream stream(fliepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{


		/*if (type == ShaderType::NONE)
			std::cout << "Shader File error" << std::endl;*/

		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}


 unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
 {
	 unsigned int id = glCreateShader(type);
	 const char* src = source.c_str();
	 glShaderSource(id, 1, &src, nullptr);
	 glCompileShader(id);

	 //Error Handling 
	 int result;
	 glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	 if (result == GL_FALSE)
	 {
		 int length;
		 glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		 char* message = (char *)alloca(length * sizeof(char));
		 glGetShaderInfoLog(id, length, &length, message);
		 std::cout << "Failed to compile"
			 << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
			 << std::endl;
		 std::cout << message << std::endl;
		 glDeleteShader(id);
		 return 0;
	 }

	 return id;
 }

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int programID = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(programID, vs);
	glAttachShader(programID, fs);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return programID;
}


void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string & name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string & name, const glm::mat4 & matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}


unsigned int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning uniform " << name << " doesn't exist..." << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
