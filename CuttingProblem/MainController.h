#pragma once

#include "ThreadCallback.h"
#include "ThreadsManager.h"

#include "wx/wx.h"

#include <ctime>

class MainController : public ThreadCallback
{
public:
	MainController(void);
	~MainController(void);

	void	Run();
	
private:
	enum STATE
	{
		NONE = 0,
		PLACEMENT,
		CROSSINGOVER,
		MUTATOR,
		SELECTOR,
	};

	virtual void		OnThreadsFinish();

	STATE				m_CurrentState;
	wxCriticalSection	m_CriticalSection;
	ThreadsManager		m_ThreadManager;
	clock_t				m_Start, m_End;

	static int			s_iRunCount;
};

