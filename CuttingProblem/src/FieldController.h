#pragma once

#include "Vector2F.h"

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

	std::vector<const RectangleF*>	FindIntersectedRectangles(RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection);
	const RectangleF*				FindClosestRectangles(RectangleF* pRectangle, const RectangleDB& rectangleDB, bool bDirection);

private:
	void							GetProjection(const RectangleF* m, const Vector2F& dir, Vector2F& min, Vector2F& max);
	bool							Intersect(RectangleF* m0, const RectangleF* m1, bool bDirection);
};

