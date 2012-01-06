#pragma once

#include "Threadable.h"

class Population;
class Chromosome;

class ICrossingover : public Threadable
{
public:
	ICrossingover(Population* pPopulation);
	virtual ~ICrossingover();

protected:
	Population*			m_pPopulation;
	

private:
	virtual void		DoEntry(void);
	virtual void		DoExit(void);
	
	virtual	Chromosome* DoCrossingover(Chromosome* parent0, Chromosome* parent1) = 0;
	
	static size_t				s_iChromosomeIndex;
	static Population*			s_pNewPopulation;

	struct IndexedChromosome
	{
		IndexedChromosome(size_t pos = 0, Chromosome* pChrom = NULL): uiPosition(pos), pChromosome(pChrom) {}
		size_t uiPosition;
		Chromosome* pChromosome;
	};
};
