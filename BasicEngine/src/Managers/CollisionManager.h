/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			CollisionManager.h
Purpose:			CollisionManager header files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/


#pragma once
#include <list>

class Body;

class Shape 
{
public:
	enum ShapeType
	{
		CIRCLE,
		AABB,
		NUM
	};

	Shape(ShapeType Type);
	virtual ~Shape() {} 

	virtual bool TestPoint(float PointX, float PointY) = 0;

public:
	Body *mpOwnerBody;
	ShapeType mType;
};


class ShapeCircle : public Shape
{
public:
	ShapeCircle(float radius);
	~ShapeCircle();

	bool TestPoint(float PointX, float PointY);

public:
	float mRadius;
};


class ShapeAABB : public Shape
{
public:
	ShapeAABB(float top, float bottom, float left , float right );
	~ShapeAABB();

	bool TestPoint(float PointX, float PointY);

public:
	float mTop,mBottom,mRight,mLeft;
};


class Contact 
{
public:
	Contact();
	~Contact() {}
public:
	Body* mpBodies[2];
};


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Reset();
	bool CheckCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y,
		Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts);

public:
	std::list<Contact *> mContacts;

private:
	//2D array of function pointers, used to stroe the collision function's address 
	bool (*CollisionFunctions[Shape::NUM][Shape::NUM]) (Shape *pShape1, float Pos1X, float Pos1Y,
													  Shape *pShape2, float Pos2X, float Pos2Y,
													  std::list<Contact *>&Contacts);

};