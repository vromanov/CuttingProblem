#include "Chromosome.h"

Chromosome::Chromosome(size_t uiGeneCount)
: m_fFitnessValue(-1.f)
, m_fProbabilityValue(-1.f)
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
	m_fProbabilityValue = pChromosome.m_fProbabilityValue;
	m_bIsPlacement = pChromosome.m_bIsPlacement;
}

Chromosome& Chromosome::operator=(const Chromosome& pChromosome)
{
	m_iRectangleQueue.clear();
	m_RectanglePlacement.Clear();

	m_iRectangleQueue = pChromosome.m_iRectangleQueue;
	m_RectanglePlacement = pChromosome.m_RectanglePlacement;
	m_fFitnessValue = pChromosome.m_fFitnessValue;
	m_fProbabilityValue = pChromosome.m_fProbabilityValue;
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

void Chromosome::InsertGene( const size_t index, const size_t gene )
{
	std::vector<int>::iterator it = m_iRectangleQueue.begin();
	std::advance(it, index);
	m_iRectangleQueue.insert(it, gene);
}

void Chromosome::DeleteGene( const size_t index )
{
	std::vector<int>::iterator it = m_iRectangleQueue.begin();
	std::advance(it, index);
	m_iRectangleQueue.erase(it);
}

void Chromosome::ReInitDB()
{
	m_RectanglePlacement.ReInit();
	SetPlacement(false);
}

void Chromosome::WipeDB()
{
	m_RectanglePlacement.Wipe();
	SetPlacement(false);
}

void Chromosome::DeleteRectangle( const size_t index )
{
	m_RectanglePlacement.DeleteRectangle(index);
}
