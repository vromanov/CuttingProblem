#pragma once

#include <vector>

class Chromosome;

class Population
{
public:
	Population(size_t uiChromosomeCount = 0);
	~Population(void);
	Population& operator=(const Population&);

	void					AddChromosome(size_t uiWhere, Chromosome* pChromosome);
	void					Clear();
	
	std::vector<Chromosome*>&	GetChromosomes() { return m_pChromosomes; }
	Chromosome*					GetChromosome(const size_t index) { return m_pChromosomes[index];}

	static Population*      GenerateRandPopulation(size_t chromosomeCount);
private:
	std::vector<Chromosome*>		m_pChromosomes;
};

