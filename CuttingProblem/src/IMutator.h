#ifndef _IMUTATOR_H_
#define _IMUTATOR_H_

#include "Threadable.h"

class Population;
class Chromosome;

class IMutator : public Threadable
{
public:
	IMutator(Population* pPopulation);
	virtual ~IMutator();

protected:
	Population*		m_pPopulation;

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	virtual void	DoMutator(Chromosome* pChromosome) = 0;

	static size_t	s_iChromosomeIndex;
};
#endif