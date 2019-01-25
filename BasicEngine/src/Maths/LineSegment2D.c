/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			LineSegment2D.c
Purpose:			LineSegment2D implementation files
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "LineSegment2D.h"



/*
This function builds a 2D line segment's data using 2 points
 - Computes the normal (Unit Vector)
 - Computes the dot product of the normal with one of the points

 - Parameters
	- LS:		The to-be-built line segment
	- Point0:	One point on the line
	- Point1:	Another point on the line

 - Returns 1 if the line equation was built successfully
*/
int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{	
	Vector2D e, e1;

	if (Point0->x == Point1->x && Point0->y == Point1->y)
		return 0;

	else {

		Vector2DSet(&LS->mP0, Point0->x, Point0->y);
		Vector2DSet(&LS->mP1, Point1->x, Point1->y);
		Vector2DSub(&e, Point1, Point0);

		Vector2DSet(&e1, e.y, -e.x);

		Vector2DNormalize(&LS->mN, &e1);

		LS->mNdotP0 = Vector2DDotProduct(&LS->mN, Point0);

		return 1;
	}
}