#ifndef _ISELECTOR_H_
#define _ISELECTOR_H_

#include "Threadable.h"

class Population;

class ISelector : public Threadable
{
public:
	ISelector(Population* pPopulation);
	virtual ~ISelector();

protected:
	Population*			m_pPopulation;

private:
	virtual void	DoEntry(void) = 0;
	virtual void	DoExit(void) = 0;
};
#endif