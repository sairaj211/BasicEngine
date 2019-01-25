/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			CollisionManager.cpp
Purpose:			CollisionManager implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "CollisionManager.h"
#include "Math2D.h"

Shape::Shape(ShapeType Type)
{
	mType = Type;
	mpOwnerBody = nullptr;
}

ShapeCircle::ShapeCircle(float radius) : Shape (CIRCLE)
{
	mRadius = radius;
}

ShapeCircle::~ShapeCircle()
{
}

bool ShapeCircle::TestPoint(float PointX, float PointY)
{
	return false;
}

ShapeAABB::ShapeAABB(float top, float bottom, float left, float right) : Shape (AABB)
{
	mTop = top;
	mBottom = bottom;
	mLeft = left;
	mRight = right;
}

ShapeAABB::~ShapeAABB()
{
}

bool ShapeAABB::TestPoint(float PointX, float PointY)
{
	return false;
}

Contact::Contact()
{
	mpBodies[0] = nullptr;
	mpBodies[1] = nullptr;
}

bool CheckCollisionAABBAABB(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2,float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	ShapeAABB *p1 = static_cast<ShapeAABB*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeAABB *p2 = static_cast<ShapeAABB*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);

	if (StaticRectToStaticRect(&Pos1, p1->mTop, p1->mLeft, &Pos2, p2->mTop, p2->mLeft))
	{
		//Create a new contact and add to the contacts list
		Contact *pNewContact = new Contact();
		pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(pNewContact);

		return true;
	}
	return false;
}

bool checkCollisionCircleCircle(Shape *pShape1, float Pos1X, float Pos1Y, 
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	ShapeCircle *p1 = static_cast<ShapeCircle*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeCircle *p2 = static_cast<ShapeCircle*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);

	if (StaticCircleToStaticCircle(&Pos1, p1->mRadius, &Pos2, p2->mRadius))
	{
		//Create a new contact and add to the contacts list
		Contact *pNewContact = new Contact();
		pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(pNewContact);

		return true;
	}

	return false;
}


bool checkCollisionCircleAABB(Shape *pShape1, float Pos1X, float Pos1Y,
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	ShapeCircle *p1 = static_cast<ShapeCircle*>(pShape1);
	Vector2D Pos1;
	Vector2DSet(&Pos1, Pos1X, Pos1Y);
	ShapeAABB *p2 = static_cast<ShapeAABB*>(pShape2);
	Vector2D Pos2;
	Vector2DSet(&Pos2, Pos2X, Pos2Y);


	//Create a new contact and add to the contacts list
	Contact *pNewContact = new Contact();
	pNewContact->mpBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mpBodies[1] = pShape2->mpOwnerBody;
	Contacts.push_back(pNewContact);

	return true;
}

bool checkCollisionAABBCircle(Shape *pShape1, float Pos1X, float Pos1Y, 
	Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	return checkCollisionCircleAABB(pShape2, Pos2X, Pos2Y, pShape1, Pos1X, Pos1Y, Contacts);
}


CollisionManager::CollisionManager()
{
	CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = checkCollisionCircleCircle;
	CollisionFunctions[Shape::CIRCLE][Shape::AABB] = checkCollisionCircleAABB;
	CollisionFunctions[Shape::AABB][Shape::AABB] = CheckCollisionAABBAABB;
	CollisionFunctions[Shape::AABB][Shape::CIRCLE] = checkCollisionAABBCircle;
}

CollisionManager::~CollisionManager()
{
	Reset();
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c;

	mContacts.clear();
}

bool CollisionManager::CheckCollisionAndGenerateContact(Shape *pShape1, float Pos1X, float Pos1Y,
						 Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact*> &Contacts)
{
	
 	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, Pos1X, Pos1Y,
		pShape2, Pos2X, Pos2Y, Contacts);
}
