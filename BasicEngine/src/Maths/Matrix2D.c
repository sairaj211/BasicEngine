/*
-------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.Reproduction or disclosure of this file
or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name:			Matrix2D.c
Purpose:			Matrix2D Library implementation
Language:			c++ and gcc compiler
Platform:			gcc 7.1.0 , Windows 10
Project:			Final Game Project (TheBasic Engine)
Project:			cs529_sairaj.padghe_1
Author:				Sairaj Padghe , sairaj.padghe	, 60003518
Creation date:		12/9/2018
--------------------------------------------------------
*/

#include "Matrix2D.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
////////////////////
// From project 2 //
////////////////////


/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{

	memset(pResult->m, 0, 9 * sizeof(float));
	pResult->m[0][0] = 1.0f;
	pResult->m[1][1] = 1.0f;
	pResult->m[2][2] = 1.0f;

}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/

void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	int i, j;

	Matrix2DIdentity(pResult);

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 3; ++j)
			pResult->m[j][i] = pMtx->m[i][j];
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D temp = { 0 };

	temp.m[0][0] = (pMtx0->m[0][0] * pMtx1->m[0][0]) + (pMtx0->m[0][1] * pMtx1->m[1][0]) + (pMtx0->m[0][2] * pMtx1->m[2][0]);
	temp.m[0][1] = (pMtx0->m[0][0] * pMtx1->m[0][1]) + (pMtx0->m[0][1] * pMtx1->m[1][1]) + (pMtx0->m[0][2] * pMtx1->m[2][1]);
	temp.m[0][2] = (pMtx0->m[0][0] * pMtx1->m[0][2]) + (pMtx0->m[0][1] * pMtx1->m[1][2]) + (pMtx0->m[0][2] * pMtx1->m[2][2]);

	temp.m[1][0] = (pMtx0->m[1][0] * pMtx1->m[0][0]) + (pMtx0->m[1][1] * pMtx1->m[1][0]) + (pMtx0->m[1][2] * pMtx1->m[2][0]);
	temp.m[1][1] = (pMtx0->m[1][0] * pMtx1->m[0][1]) + (pMtx0->m[1][1] * pMtx1->m[1][1]) + (pMtx0->m[1][2] * pMtx1->m[2][1]);
	temp.m[1][2] = (pMtx0->m[1][0] * pMtx1->m[0][2]) + (pMtx0->m[1][1] * pMtx1->m[1][2]) + (pMtx0->m[1][2] * pMtx1->m[2][2]);

	temp.m[2][0] = (pMtx0->m[2][0] * pMtx1->m[0][0]) + (pMtx0->m[2][1] * pMtx1->m[1][0]) + (pMtx0->m[2][2] * pMtx1->m[2][0]);
	temp.m[2][1] = (pMtx0->m[2][0] * pMtx1->m[0][1]) + (pMtx0->m[2][1] * pMtx1->m[1][1]) + (pMtx0->m[2][2] * pMtx1->m[2][1]);
	temp.m[2][2] = (pMtx0->m[2][0] * pMtx1->m[0][2]) + (pMtx0->m[2][1] * pMtx1->m[1][2]) + (pMtx0->m[2][2] * pMtx1->m[2][2]);

	*pResult = temp;

}
// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][2] = x;
	pResult->m[1][2] = y;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = x;
	pResult->m[1][1] = y;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	Matrix2DRotRad(pResult, Angle*((float)PI / 180.0f));
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	Matrix2DIdentity(pResult);
	pResult->m[0][0] = (float)cos(Angle);
	pResult->m[0][1] = (float)-sin(Angle);
	pResult->m[1][0] = (float)sin(Angle);
	pResult->m[1][1] = (float)cos(Angle);
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D temp;
	temp.x = (pMtx->m[0][0] * pVec->x) + (pMtx->m[0][1] * pVec->y) + (pMtx->m[0][2] * 1);
	temp.y = (pMtx->m[1][0] * pVec->x) + (pMtx->m[1][1] * pVec->y) + (pMtx->m[1][2] * 1);

	*pResult = temp;
}

// ---------------------------------------------------------------------------
