#pragma once

#include "IMutator.h"

class Chromosome;
class MutatorChange : public IMutator
{
public:
	MutatorChange(Population* pPopulation);
	~MutatorChange(void);

private:
	virtual void	DoMutator(Chromosome* pChromosome);
};

