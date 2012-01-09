#pragma once

#include "IMutator.h"

class Chromosome;
class MutatorXuInsert : public IMutator
{
public:
	MutatorXuInsert(Population* pPopulation);
	~MutatorXuInsert(void);
	
private:
	virtual void	DoMutator(Chromosome* pChromosome);
};

