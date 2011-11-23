#pragma once

#include "ThreadCallback.h"
#include "ThreadsManager.h"

#include "wx/wx.h"

#include <ctime>

class Threadable;

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
	
	template<typename T>
	void				DoRun(T* pClass);
	virtual void		OnThreadsFinish();

	STATE				m_CurrentState;
	wxCriticalSection	m_CriticalSection;
	ThreadsManager		m_ThreadManager;
	clock_t				m_Start, m_End;

	static int			s_iRunCount;
};

template<typename T>
void MainController::DoRun(T* pClass)
{
	wxLogDebug("MainController::DoRun called");

	if (s_iRunCount == 0 && m_CurrentState == NONE)
		m_Start = clock();
	else if (s_iRunCount == 6)
	{
		m_End = clock();
		double time = (double)(m_End - m_Start) / CLOCKS_PER_SEC;
		wxLogError("time = %f", time);
		s_iRunCount = 0;
		return;
	}

	if (m_CurrentState == NONE)
		m_CurrentState = CROSSINGOVER;

	m_ThreadManager.Register(this);
	m_ThreadManager.Run(pClass);
}
