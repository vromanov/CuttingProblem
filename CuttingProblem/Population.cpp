#include "Population.h"

#include "Chromosome.h"

Population::Population(size_t uiChromosomeCount)
{
	m_pChromosomes.resize(uiChromosomeCount);
}

Population::~Population(void)
{
	
}

Population* Population::GenerateRandPopulation( size_t chromosomeCount )
{
	Population* population = new Population(chromosomeCount);
	for (size_t i = 0; i < chromosomeCount; ++i)
	{
		population->AddChromosome(i, Chromosome::GenerateRandChromosome());
	}
	return population;
}

void Population::Clear()
{
	for (size_t i = 0, i_end = m_pChromosomes.size(); i < i_end; ++i)
	{
		delete m_pChromosomes[i];
		m_pChromosomes[i] = NULL;
	}
	m_pChromosomes.clear();
}

void Population::AddChromosome(size_t uiWhere, Chromosome* pChromosome )
{
	m_pChromosomes[uiWhere] = pChromosome;
}

Population& Population::operator=( const Population& population)
{
	Clear();
	size_t  chromosomeCount = population.m_pChromosomes.size();
	m_pChromosomes.resize(chromosomeCount);

	for (size_t i = 0; i < chromosomeCount; ++i)
	{
		Chromosome* pCopy = new Chromosome(*(population.m_pChromosomes[i]));
		AddChromosome(i, pCopy);
	}

	return *this;
}
