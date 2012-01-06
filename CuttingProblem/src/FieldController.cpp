#include "FieldController.h"

#include "RectangleF.h"
#include "RectangleDB.h"


#include <iostream>

FieldController::FieldController(void)
{
}


FieldController::~FieldController(void)
{
}


void FieldController::GetProjection(const RectangleF* pRect, const Vector2F& dir, Vector2F& min, Vector2F& max)
{
	Vector2F	projectionAxis(-dir.Y(), dir.X());
	float		sqrlen = projectionAxis.X() * projectionAxis.X() + projectionAxis.Y() * projectionAxis.Y();


	// projection rectangle points to projAxis
	float dp = pRect->GetTopLeft().X() * projectionAxis.X() + pRect->GetTopLeft().Y() * projectionAxis.Y();
	float tempValue = dp / sqrlen;

	min.X() = tempValue * projectionAxis.X();
	min.Y() = tempValue * projectionAxis.Y();

	dp = pRect->GetBottomRight().X() * projectionAxis.X() + pRect->GetBottomRight().Y() * projectionAxis.Y();
	tempValue = dp / sqrlen;

	max.X() = tempValue * projectionAxis.X();
	max.Y() = tempValue * projectionAxis.Y();

}

bool FieldController::Intersect(RectangleF* m0, const RectangleF* m1, bool bDirection)
{
	Vector2F dir;

	if (bDirection && (m0->GetBottomRight().Y() > m1->GetTopLeft().Y()))
		return false;


	if (bDirection)
		dir = Vector2F(0, 1);
	else
		dir = Vector2F(1, 0);

	Vector2F min0, max0, min1, max1;
	GetProjection(m0, dir, min0, max0);
	GetProjection(m1, dir, min1, max1);

	//if (max0.X() > min1.X() || max0.Y() > min1.Y())
	//	return true;

	if (bDirection)
	{
		if ((max0.X() > min1.X() && max0.X() < max1.X()) ||
			(min0.X() > min1.X() && min0.X() < max1.X()) ||
			(max1.X() > min0.X() && max1.X() < max0.X()) ||
			(min1.X() > min0.X() && min1.X() < max0.X()) ||
			min0.X() == min1.X() || max0.X() == max1.X())
			return true;
	}
	else
	{
		if ((max0.Y() > min1.Y() && max0.Y() < max1.Y()) ||
			(min0.Y() > min1.Y() && min0.Y() < max1.Y()) ||
			(max1.Y() > min0.Y() && max1.Y() < max0.Y()) ||
			(min1.Y() > min0.Y() && min1.Y() < max0.Y()) ||
			min0.Y() == min1.Y() || max0.Y() == max1.Y())
			return true;
	}

	return false;
}

std::vector<const RectangleF*> FieldController::FindIntersectedRectangles(RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection)
{
	std::vector<const RectangleF*> res;

	for (int k = 0, k_end = rectangleDB.Size(); k < k_end; ++k)
	{
		const RectangleF* pRect = rectangleDB[k];
		if(pRect->GetStatus() == ON_FIELD)
		{
			if (Intersect(pRectangle, rectangleDB[k], bDirection))
			{
				res.push_back(rectangleDB[k]);
			}
		}
	}

	return res;
}


const RectangleF* FieldController::FindClosestRectangles(RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection)
{
	std::vector<const RectangleF*> pModels = FindIntersectedRectangles(pRectangle, rectangleDB, bDirection);

	const RectangleF* pResultModel = NULL;

	Vector2F projectionAxis;
	if (!bDirection)
		projectionAxis = Vector2F(0, 1);
	else
		projectionAxis = Vector2F(1, 0);

	Vector2F min, max, modelMin, modelMax;
	float minLength = 12345678;

	GetProjection(pRectangle, projectionAxis, modelMin, modelMax);

	for (int i = 0, i_end = pModels.size(); i < i_end; ++i)
	{
		GetProjection(pModels[i], projectionAxis, min, max);
		// we are interested in one side models only 
		if (min > modelMin)
		{
			Vector2F lengthVec = (modelMax - min);
			float tempLength = lengthVec.X() * lengthVec.X() + lengthVec.Y() * lengthVec.Y();
			if (tempLength < minLength)
			{
				pResultModel = pModels[i];
				minLength = tempLength;
			}
		}
	}

	return pResultModel;
}