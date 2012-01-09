#pragma once

#include "Vector2F.h"
#include "Segment.h"

#include <vector>

class RectangleF;
class RectangleDB;

enum {
	HORIZONTAL_DIRECTION,
	VERTICAL_DIRECTION
};

enum {
	DOWN_MODELS
};

class FieldController
{
public:
	FieldController(void);
	~FieldController(void);

	std::vector<const RectangleF*>	FindIntersectedRectangles(const RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection);
	const RectangleF*				FindClosestRectangles(RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection);
	const size_t					FindBigestHolePosition(const RectangleDB& rectangleDB);

private:
	void							GetProjection(const RectangleF* m, const Vector2F& dir, Vector2F& min, Vector2F& max);
	bool							Intersect(const RectangleF* m0, const RectangleF* m1, bool bDirection);
	float							GetHoleSquad(const RectangleF* pRectangle, const RectangleDB& db);
	void							SortSegmetnsByY( std::vector<Segment>& modelTopLine );
	void							LinesCalibrate( const Segment& topSegment, std::vector<Segment>& modelTopLine );
	float							HoleSquad( const Segment& topSegment, const std::vector<Segment>& modelTopLine );
};

