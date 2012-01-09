#pragma once
#include "ISelector.h"

class Population;

class SelectorElitarizm : public ISelector
{
public:
    SelectorElitarizm(Population* pPopulation);
    virtual ~SelectorElitarizm(void);

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	static bool		bIsDone;
};

