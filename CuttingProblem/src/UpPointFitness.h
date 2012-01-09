#ifndef _UPPOINT_FITNESS_H_
#define _UPPOINT_FITNESS_H_

#include "IFitness.h"

class Population;

class UpPointFitness : public IFitness
{
public:
    UpPointFitness(Population* pPopulation);
    ~UpPointFitness(void);

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	static size_t s_iChromosomeIndex;
};

#endif
