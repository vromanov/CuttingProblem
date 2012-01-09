#pragma once

#include "ICrossingover.h"

class Chromosome;

class CrossingoverOX : public ICrossingover
{
public:
	CrossingoverOX(Population* pPopulation);
	~CrossingoverOX();
private:
	virtual size_t		GetCrossPoint( Chromosome* pParent );

	virtual	Chromosome* DoCrossingover(Chromosome* parent0, Chromosome* parent1);
};