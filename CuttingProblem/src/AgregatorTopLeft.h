#ifndef _TOPLEFT_AGREGATOR_H_
#define _TOPLEFT_AGREGATOR_H_

#include "IAgregator.h"

class Population;
class RectangleF;
class RectangleDB;
class Chromosome;

class AgregatorTopLeft : public IAgregator
{
public:
	AgregatorTopLeft(Population* pPopulation);
	~AgregatorTopLeft();

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	void			SetRectangleOnField(RectangleF* pRectangle, Chromosome* pChromosome);

	Population*		m_pPopulation;

	static size_t	s_iChromosomeIndex;
};

#endif