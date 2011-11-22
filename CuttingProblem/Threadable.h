#pragma once

#include "Utils.h"

#include "wx/thread.h"

class ThreadCallback;

class Threadable : public wxThread
{
public:
	Threadable();
	~Threadable();

	virtual void*	Entry(void);
	virtual void	OnExit();
	void			Register(ThreadCallback* pCallback);

private:
	virtual void	DoEntry() = 0;
	virtual void	DoExit() = 0;

	ThreadCallback*		m_pCallback;
	wxCriticalSection	m_CriticalSection;

	static size_t		s_iCurrentThread;
};
