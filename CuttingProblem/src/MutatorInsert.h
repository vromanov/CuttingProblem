#pragma once

#include "IMutator.h"

class Chromosome;
class MutatorInsert : public IMutator
{
public:
	MutatorInsert(Population* pPopulation);
	~MutatorInsert(void);
	
private:
	virtual void	DoMutator(Chromosome* pChromosome);
};

