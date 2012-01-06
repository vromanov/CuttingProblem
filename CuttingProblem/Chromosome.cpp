#include "Chromosome.h"

Chromosome::Chromosome(size_t uiGeneCount)
: m_fFitnessValue(0)
, m_bIsPlacement(false)
{
	m_iRectangleQueue.resize(uiGeneCount);
}

Chromosome::~Chromosome()
{
	m_iRectangleQueue.clear();
}

Chromosome::Chromosome( const Chromosome& pChromosome)
{
	m_iRectangleQueue.clear();
	m_RectanglePlacement.Clear();

	m_iRectangleQueue = pChromosome.m_iRectangleQueue;
	m_RectanglePlacement = pChromosome.m_RectanglePlacement;
	m_fFitnessValue = pChromosome.m_fFitnessValue;
	m_bIsPlacement = pChromosome.m_bIsPlacement;
}

Chromosome& Chromosome::operator=(const Chromosome& pChromosome)
{
	m_iRectangleQueue.clear();
	m_RectanglePlacement.Clear();

	m_iRectangleQueue = pChromosome.m_iRectangleQueue;
	m_RectanglePlacement = pChromosome.m_RectanglePlacement;
	m_fFitnessValue = pChromosome.m_fFitnessValue;
	m_bIsPlacement = pChromosome.m_bIsPlacement;

	return *this;
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