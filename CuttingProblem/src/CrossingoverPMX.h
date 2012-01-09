#pragma once

#include "ICrossingover.h"

class Population;
class Chromosome;
class CrossingoverPMX : public ICrossingover
{
public:
	CrossingoverPMX(Population* population);
	~CrossingoverPMX(void);

private:
	virtual Chromosome* DoCrossingover( Chromosome* pParent0, Chromosome* pParent1 );

	int	findSameGene(const int& gene, const Chromosome& chromosome, int pos0, int pos1);
};

