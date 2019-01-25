/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Math2D.c
Purpose:			Math2D Library Implementation
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Math2D.h"
#include "stdio.h"

////////////////////
// From Project 1 //
////////////////////


/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	return (Vector2DSquareDistance(pP, pCenter) <= (Radius * Radius)) ? 1 : 0;
}

/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	float Left, Right, Bottom, Top;

	Left = pRect->x - Width / 2;
	Right = pRect->x + Width / 2;
	Bottom = pRect->y - Height / 2;
	Top = pRect->y + Height / 2;

	return (pPos->x < Left || pPos->x > Right || pPos->y < Bottom || pPos->y > Top) ? 0 : 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	float RadiusSum = Radius0 + Radius1;
	float centersDistance = Vector2DSquareDistance(pCenter0, pCenter1);

	return (centersDistance <= (RadiusSum*RadiusSum)) ? 1 : 0;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float Left1, Right1, Top1, Bottom1;
	float Left2, Right2, Top2, Bottom2;

	Left1 = pRect0->x - Width0 / 2;
	Right1 = pRect0->x + Width0 / 2;
	Bottom1 = pRect0->y - Height0 / 2;
	Top1 = pRect0->y + Height0 / 2;

	Left2 = pRect1->x - Width1 / 2;
	Right2 = pRect1->x + Width1 / 2;
	Bottom2 = pRect1->y - Height1 / 2;
	Top2 = pRect1->y + Height1 / 2;

	return (Left1 > Right2 || Left2 > Right1 || Top1 < Bottom2 || Top2 < Bottom1) ? 0 : 1;

}

//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	float result;
	result = Vector2DDotProduct(&LS->mN, P) - LS->mNdotP0;
	return result;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{

	float intersectionTime = -1.0f, n_dot_vBar, n_dot_Ps, n_dot_Pe;
	Vector2D vBar, vecT, Pi_P0, Pi_P1, P0_P1, P1_P0;


	Vector2DSub(&vBar, Pe, Ps);

	n_dot_vBar = Vector2DDotProduct(&LS->mN, &vBar);

	n_dot_Ps = Vector2DDotProduct(&LS->mN, Ps);

	n_dot_Pe = Vector2DDotProduct(&LS->mN, Pe);

	if ((n_dot_Ps < LS->mNdotP0) && (n_dot_Pe < LS->mNdotP0))
		return -1.0f;
	else if ((n_dot_Ps > LS->mNdotP0) && (n_dot_Pe > LS->mNdotP0))
		return -1.0f;
	else if (n_dot_vBar == 0)
		return -1.0f;

	intersectionTime = ((LS->mNdotP0) - n_dot_Ps) / n_dot_vBar;

	Vector2DScale(&vecT, &vBar, intersectionTime);
	Vector2DAdd(Pi, Ps, &vecT);

	Vector2DSub(&Pi_P0, Pi, &LS->mP0);

	Vector2DSub(&Pi_P1, Pi, &LS->mP1);

	Vector2DSub(&P0_P1, &LS->mP0, &LS->mP1);

	Vector2DSub(&P1_P0, &LS->mP1, &LS->mP0);


	if (Vector2DDotProduct(&Pi_P0, &P1_P0) < 0.f)
		return -1.0f;
	else if (Vector2DDotProduct(&Pi_P1, &P0_P1) < 0.f)
		return -1.0f;
	else if (intersectionTime > 0.f || intersectionTime < 1.f)
		return intersectionTime;

	return -1.0f;

}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{

	float intersectionTime, n_dot_vBar, n_dot_Ps, n_dot_Pe, x;
	Vector2D vBar, vecT, Pi_P0, Pi_P1, P0_P1, P1_P0;

	float P0_normal = LS->mNdotP0, collision;

//	Vector2D multiply;

	Vector2DSub(&vBar, Pe, Ps);

	x = Vector2DLength(&vBar);


	n_dot_vBar = Vector2DDotProduct(&LS->mN, &vBar);

	n_dot_Ps = Vector2DDotProduct(&LS->mN, Ps);

	n_dot_Pe = Vector2DDotProduct(&LS->mN, Pe);

	collision = StaticPointToStaticLineSegment(Ps, LS);

	if (collision < 0.f)
		Radius *= -1;


	if (((n_dot_Ps - P0_normal < Radius)) && ((n_dot_Pe - P0_normal) < Radius))
		return -1.f;
	else if (((n_dot_Ps - P0_normal) > Radius) && ((n_dot_Pe - P0_normal) > Radius))
		return -1.f;

	intersectionTime = (P0_normal - n_dot_Ps + Radius) / n_dot_vBar;


	Vector2DScale(&vecT, &vBar, intersectionTime);

	Vector2DAdd(Pi, Ps, &vecT);

	Vector2DSub(&Pi_P0, Pi, &LS->mP0);

	Vector2DSub(&Pi_P1, Pi, &LS->mP1);

	Vector2DSub(&P0_P1, &LS->mP0, &LS->mP1);

	Vector2DSub(&P1_P0, &LS->mP1, &LS->mP0);

	if (Vector2DDotProduct(&Pi_P1, &P0_P1) < 0.f)
		return -1.f;
	else if (Vector2DDotProduct(&Pi_P0, &P1_P0) < 0.f)
		return -1.f;
	// BUT !! We have a problem ....
	else if (intersectionTime > 0.f || intersectionTime < 1.f)
		return intersectionTime;

	return -1.f;

}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D vecPI, vecSbar;
	float sBar, intersectionTime;

	intersectionTime = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);

	if (intersectionTime == -1.f)
		return intersectionTime;


	Vector2DSub(&vecPI, Pe, Pi);

	sBar = Vector2DDotProduct(&vecPI, &LS->mN);

	Vector2DScale(&vecSbar, &LS->mN, 2 * sBar);

	//Vector2DScale(&vecSbar, &vecSbar, 2.0f);

	Vector2DSub(R, &vecPI, &vecSbar);

	return intersectionTime;
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D vecPI, vecSbar;
	float sBar, intersectionTime;

	intersectionTime = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);

	if (intersectionTime == -1.f)
		return intersectionTime;

	//	AESYSprin("intersection time = %f", intersectionTime);

	Vector2DSub(&vecPI, Pe, Pi);

	sBar = Vector2DDotProduct(&vecPI, &LS->mN);

	Vector2DScale(&vecSbar, &LS->mN, 2 * sBar);

	//	Vector2DScale(&vecSbar, &vecSbar, 2.0f);

	Vector2DSub(R, &vecPI, &vecSbar);

	return intersectionTime;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{

	// 2nd Method

	Vector2D vBar, PsC_bar, norm_V;
	float magnitude_V, m, length_Ps_C, n_square, s_square, t0, t1;

	Vector2DSub(&vBar, Pe, Ps);

	Vector2DSub(&PsC_bar, Center, Ps);
	Vector2DNormalize(&norm_V, &vBar);

	/*m = BsC * (normalized V)*/
	m = Vector2DDotProduct(&PsC_bar, &norm_V);

	length_Ps_C = Vector2DSquareLength(&PsC_bar);

	/*n_square = length_Ps_c - m_square*/
	n_square = length_Ps_C - (m*m);

	//AESysPrintf("radius = %f\n", Radius*Radius);
	//AESysPrintf("Distance = %f\n", Vector2DSquareDistance(Center, Ps));


	if (m < 0 && (Vector2DSquareDistance(Center, Ps) > Radius*Radius))
		return -1.f;
	else if (n_square > Radius*Radius)
		return -1.f;

	s_square = (Radius*Radius) - n_square;

	magnitude_V = Vector2DLength(&vBar);

	t0 = (float)(m - sqrt(s_square)) / magnitude_V;
	t1 = (float)(m + sqrt(s_square)) / magnitude_V;

	if (t0 > t1) {
		Vector2DScaleAdd(Pi, &vBar, Ps, t1);
		return t1;
	}
	else {
		Vector2DScaleAdd(Pi, &vBar, Ps, t0);
		return t0;
	}

	return -1.0f;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	Vector2D v_Bar, n_Bar, norm_n, m_Bar, u_Bar, norm_r, r;
	float intersectionTime, temp, k;
	/*Compute Pi : Pi = Ps + v_Bar * intersection time*/

	Vector2DSub(&v_Bar, Pe, Ps);
	intersectionTime = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);

	if (intersectionTime == -1.f)
		return intersectionTime;
	else if (intersectionTime < 0.f || intersectionTime > 1.f)
		return -1.f;
	else {
		Vector2DSub(&n_Bar, Center, Pi);
		Vector2DNormalize(&norm_n, &n_Bar);

		Vector2DSub(&m_Bar, Ps, Pi);

		temp = Vector2DDotProduct(&m_Bar, &norm_n);
		Vector2DScale(&u_Bar, &norm_n, temp);

		Vector2DScaleSub(&r, &u_Bar, &m_Bar, 2);

		Vector2DNormalize(&norm_r, &r);

		k = Vector2DLength(&v_Bar);

		//Vector2DScaleAdd(R, &norm_r, Pi, k*(1 - intersectionTime));
	//	Vector2DAdd(R, Pi, &norm_r);
		Vector2DScale(R, &norm_r, k*(1 - intersectionTime));

		return intersectionTime;
	}
	return -1.0f;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center
	- Center0e:		The ending position of the animated circle's center
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{


	return AnimatedPointToStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi);

}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one

 - Parameters
	- Center0s:		The starting position of the animated circle's center
	- Center0e:		The ending position of the animated circle's center
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{

	return ReflectAnimatedPointOnStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi, R);

}
