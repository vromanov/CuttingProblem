#ifndef _REBLOCKER_H_
#define _REBLOCKER_H_

#include "Threadable.h"

class Population;
class Chromosome;
class RectangleF;

class Reblocker : public Threadable
{
public:
	Reblocker(Population* pPopulation);
	virtual ~Reblocker();

protected:
	Population*		m_pPopulation;

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	bool			DoReblock(Chromosome* pChromosome);
	bool			CheckHorizontalOneSide(RectangleF* pRec0, RectangleF* pRec1);
	bool			CheckVerticalOneSide(RectangleF* pRec0, RectangleF* pRec1);
	static size_t	s_iChromosomeIndex;
};
#endif