#pragma once
#include "CrossingoverOX.h"

#include <vector>

class Chromosome;
class RectangleDB;
class RectangleF;
class Segment;

class CrossingoverXuOX : public CrossingoverOX
{
public:
	CrossingoverXuOX(Population* population);
	virtual ~CrossingoverXuOX(void);
private:
	virtual size_t	GetCrossPoint( Chromosome* pParent );
};

