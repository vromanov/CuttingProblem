#pragma once

#include "ICrossingover.h"

class CrossingoveOX : public ICrossingover
{
public:
	CrossingoveOX();
	~CrossingoveOX();
private:
	wxCriticalSection m_CriticalSection;

	virtual void	DoEntry(void);
	virtual void	DoExit();

	// for test
	static float j;
	long x, z;
};