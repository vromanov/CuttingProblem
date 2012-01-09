#ifndef _IFITNESS_H_
#define _IFITNESS_H_

#include "Threadable.h"

#include "wx/wx.h"

class Population;

class IFitness : public Threadable
{
public:
	IFitness(Population* pPopulation) : m_pPopulation(pPopulation) {}
	virtual ~IFitness() {}

protected:
	Population*			m_pPopulation;

private:
	virtual void	DoEntry(void) = 0;
	virtual void	DoExit(void) = 0;
};
#endif
