#include "Chromosome.h"

Chromosome::Chromosome()
: m_fFitnessValue(0)
, m_bIsPlacement(false)
{

}

Chromosome::~Chromosome()
{
	m_iRectangleQueue.clear();
}

/*static*/Chromosome* Chromosome::GenerateRandChromosome()
{
	Chromosome* pChromosome = new Chromosome();
	const int CHROMOSOME_SIZE = pChromosome->m_RectanglePlacement.Size();
	for (int i = 0; i < CHROMOSOME_SIZE; ++i)
		pChromosome->m_iRectangleQueue.push_back(i);

	int i = 0;
	while (i < CHROMOSOME_SIZE)
	{
		int iGene1Position = rand() % CHROMOSOME_SIZE;
		int iGene2Position = rand() % CHROMOSOME_SIZE;
		int tempGene = pChromosome->m_iRectangleQueue[iGene1Position];
		pChromosome->m_iRectangleQueue[iGene1Position] = pChromosome->m_iRectangleQueue[iGene2Position];
		pChromosome->m_iRectangleQueue[iGene2Position] = tempGene;

		++i;
	}
	return pChromosome;
}