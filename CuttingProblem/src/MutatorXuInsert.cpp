#include "MutatorXuInsert.h"
#include "Chromosome.h"
#include "FieldController.h"

#include <ctime>

MutatorXuInsert::MutatorXuInsert(Population* pPopulation)
: IMutator(pPopulation)
{
}


MutatorXuInsert::~MutatorXuInsert(void)
{
}


void MutatorXuInsert::DoMutator(Chromosome* pChromosome)
{
	FieldController fieldCtrl;
	Chromosome& chromosome = *pChromosome;

	size_t holePosition = fieldCtrl.FindBigestHolePosition(pChromosome);
	size_t chromosomeSize = chromosome.Size();

	size_t rectPositionAfterHole = rand() % chromosomeSize;
	while (rectPositionAfterHole == 0 || rectPositionAfterHole == chromosomeSize)
		rectPositionAfterHole = rand() % chromosomeSize;

	// if hole exists we get rectangle after hole position
	if (holePosition != 0 && holePosition < chromosomeSize - 1)
	{
		while (rectPositionAfterHole <= holePosition)
		{
			rectPositionAfterHole = rand() % chromosomeSize;
		}
	}

	int gene = chromosome.GetGene(rectPositionAfterHole);

	chromosome.DeleteGene(rectPositionAfterHole);
	chromosome.InsertGene(holePosition, gene);
}
