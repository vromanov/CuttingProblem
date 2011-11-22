#pragma once

#include "Threadable.h"

#include "wx/wx.h"

class ICrossingover : public Threadable
{
public:
	ICrossingover(void) {}
	~ICrossingover(void) {}
private:
	wxCriticalSection m_CriticalSection;

	virtual void	DoEntry(void);
	virtual void	DoExit();

	// for test
	static float j;
	long x, z;
};