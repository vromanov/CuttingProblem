#pragma once

#include "ICrossingover.h"

class Chromosome;

class CrossingoverOX : public ICrossingover
{
public:
	CrossingoverOX(Population* pPopulation);
	~CrossingoverOX();
private:
	size_t				GetCrossPoint(size_t chromosomeSize);

	virtual	Chromosome* DoCrossingover(Chromosome* parent0, Chromosome* parent1);
};