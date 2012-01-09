#pragma once
#include "ISelector.h"

class Population;

class SelectorRoulette: public ISelector
{
public:
	SelectorRoulette(Population* pPopulation);
	virtual ~SelectorRoulette(void);

private:
	virtual void	DoEntry(void);
	virtual void	DoExit(void);

	static bool		bIsDone;
};

