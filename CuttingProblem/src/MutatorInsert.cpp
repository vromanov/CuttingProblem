#include "MutatorInsert.h"
#include "Chromosome.h"

#include <ctime>

MutatorInsert::MutatorInsert(Population* pPopulation)
: IMutator(pPopulation)
{
}


MutatorInsert::~MutatorInsert(void)
{
}


void MutatorInsert::DoMutator(Chromosome* pChromosome)
{
	Chromosome& chromosome = *pChromosome;

	int position0 = rand() % chromosome.Size();
	int position1 = rand() % chromosome.Size();
	while (position1 == position0)
		position1 = rand() % chromosome.Size();

	int gene = chromosome.GetGene(position0);

	chromosome.DeleteGene(position0);
	chromosome.InsertGene(position1, gene);
}
