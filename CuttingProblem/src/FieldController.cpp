#include "FieldController.h"

#include "RectangleF.h"
#include "RectangleDB.h"
#include "Chromosome.h"

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

bool FieldController::Intersect(const RectangleF* m0, const RectangleF* m1, bool bDirection)
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

float FieldController::GetHoleSquad(const RectangleF* pRectangle, Chromosome* pChromosome)
{
	std::vector<const RectangleF*> intersectedModels = FindIntersectedRectangles(pRectangle, pChromosome, VERTICAL_DIRECTION);

	if (intersectedModels.empty())
		return 0;

	std::vector<Segment> modelTopLine;
	modelTopLine.reserve(intersectedModels.size());


	std::vector<const RectangleF*>::const_iterator it_intersectedModels = intersectedModels.begin();
	while (it_intersectedModels != intersectedModels.end())
	{
		const RectangleF& rectangle = **it_intersectedModels;
		Segment topSegment(rectangle.GetTopLeft(), Vector2F(rectangle.GetBottomRight().X(), rectangle.GetTopLeft().Y()));
		modelTopLine.push_back(topSegment);
		++it_intersectedModels;
	}

	Segment topSegment(Vector2F(pRectangle->GetTopLeft().X(), pRectangle->GetBottomRight().Y()), pRectangle->GetBottomRight());
	LinesCalibrate(topSegment, modelTopLine);

	return HoleSquad(topSegment, modelTopLine);
}

void FieldController::SortSegmetnsByY( std::vector<Segment>& modelTopLine )
{
	for (int i = 0, i_end = modelTopLine.size(); i < i_end; ++i)
	{
		for (int j = i, j_end = modelTopLine.size(); j < j_end; ++j)
		{
			if (modelTopLine[j].start().Y() < modelTopLine[i].start().Y())
			{
				Segment tmp = modelTopLine[j];
				modelTopLine[j] = modelTopLine[i];
				modelTopLine[i] = tmp;
			}
		}
	}
}

void FieldController::LinesCalibrate( const Segment& topSegment, std::vector<Segment>& modelTopLine )
{
	std::vector<Segment>::iterator  it_modelTopLine = modelTopLine.begin();
	while (it_modelTopLine != modelTopLine.end())
	{
		if (it_modelTopLine->start().X() < topSegment.start().X())
			it_modelTopLine->start().X() = topSegment.start().X();
		if (it_modelTopLine->end().X() > topSegment.end().X())
			it_modelTopLine->end().X() = topSegment.end().X();
		++it_modelTopLine;
	}
	SortSegmetnsByY(modelTopLine);


	Segment temp(Vector2F(1.f, 1.f), Vector2F(5.f, 1.f));
	bool res = temp.inside(Vector2F(1.f, 1.f));
	res = temp.inside(Vector2F(5.f, 1.f));
	res = temp.inside(Vector2F(4.f, 1.f));
	res = temp.inside(Vector2F(5.1f, 1.f));
	res = temp.inside(Vector2F(0.9f, 1.f));

	for (int i = 0, i_end = modelTopLine.size(); i < i_end; ++i)
	{
		for (int j = i + 1, j_end = modelTopLine.size(); j < j_end; ++j)
		{
			bool startInside = (modelTopLine[i].start().X() <= modelTopLine[j].start().X()) && (modelTopLine[j].start().X() <= modelTopLine[i].end().X());
			bool endInside = (modelTopLine[i].start().X() <= modelTopLine[j].end().X()) && (modelTopLine[j].end().X() <= modelTopLine[i].end().X());
			if (startInside && endInside)
			{
				it_modelTopLine = modelTopLine.begin();
				std::advance(it_modelTopLine, j);
				modelTopLine.erase(it_modelTopLine);
				i_end = j_end = modelTopLine.size();
				i = j = 0;
			}
			else if (startInside)
			{
				modelTopLine[j].start().X() = modelTopLine[i].end().X();
			}
			else if (endInside)
			{
				modelTopLine[j].end().X() = modelTopLine[i].start().X();
			}
			else if (modelTopLine[i].start().X() > modelTopLine[j].start().X() && modelTopLine[i].end().X() < modelTopLine[j].end().X())
			{
				modelTopLine.push_back(Segment(modelTopLine[j].start(), Vector2F(modelTopLine[i].start().X(), modelTopLine[j].start().Y())));
				modelTopLine.push_back(Segment(Vector2F(modelTopLine[i].end().X(), modelTopLine[j].end().Y()), modelTopLine[j].end()));
				it_modelTopLine = modelTopLine.begin();
				std::advance(it_modelTopLine, j);
				modelTopLine.erase(it_modelTopLine);
				i_end = j_end = modelTopLine.size();
			}
		}
	}
}

float FieldController::HoleSquad( const Segment& topSegment, const std::vector<Segment>& modelTopLine )
{
	double holeSquad = 0;
	for (int i = 0, i_end = modelTopLine.size(); i < i_end; ++i)
	{
		double a_length = modelTopLine[i].length();
		double b_length = Segment(modelTopLine[i].start(), Vector2F(modelTopLine[i].start().X(), topSegment.start().Y())).length();
		holeSquad += a_length * b_length;
	}

	return (float)holeSquad;
}

std::vector<const RectangleF*> FieldController::FindIntersectedRectangles(const RectangleF* pRectangle, Chromosome* pChromosome, bool bDirection)
{
	std::vector<const RectangleF*> res;

	for (int k = 0, k_end = pChromosome->Size(); k < k_end; ++k)
	{
		const RectangleF* pRect = pChromosome->GetRectangle(pChromosome->GetGene(k));
		if(pRect && pRect->GetStatus() == ON_FIELD)
		{
			if (Intersect(pRectangle, pRect, bDirection))
			{
				res.push_back(pRect);
			}
		}
	}

	return res;
}


const RectangleF* FieldController::FindClosestRectangles(RectangleF* pRectangle, Chromosome* pChromosome, bool bDirection)
{
	std::vector<const RectangleF*> pModels = FindIntersectedRectangles(pRectangle, pChromosome, bDirection);

	const RectangleF* pResultModel = NULL;

	Vector2F projectionAxis;
	if (!bDirection)
		projectionAxis = Vector2F(0, 1);
	else
		projectionAxis = Vector2F(1, 0);

	Vector2F min, max, modelMin, modelMax;
	float minLength = 12345678.f;

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

const size_t FieldController::FindBigestHolePosition(Chromosome* pChromosome )
{
	float fMaxHoleSquad = 0;
	size_t crossPoint = 0;

	for (size_t i = 0, i_end = pChromosome->Size(); i < i_end; ++i)
	{
		const RectangleF* pRect = pChromosome->GetRectangle(pChromosome->GetGene(i));
		if (!pRect)
			continue;
		float tmpSquad = GetHoleSquad(pRect, pChromosome);
		if (fMaxHoleSquad < tmpSquad)
		{
			fMaxHoleSquad = tmpSquad;
			crossPoint = i;
		}
	}

	return crossPoint;
}
