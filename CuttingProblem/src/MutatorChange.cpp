#include "MutatorChange.h"
#include "Chromosome.h"

MutatorChange::MutatorChange(Population* pPopulation)
: IMutator(pPopulation)
{
}


MutatorChange::~MutatorChange(void)
{
}

void MutatorChange::DoMutator(Chromosome* pChromosome)
{
	Chromosome& chromosome = *pChromosome;

	int position0 = rand() % chromosome.Size();
	int position1 = rand() % chromosome.Size();
	while (position1 == position0)
		position1 = rand() % chromosome.Size();
	int gene = chromosome.GetGene(position0);
	chromosome.SetGene(position0, chromosome.GetGene(position1));
	chromosome.SetGene(position1, gene);
}
