#pragma once

#include "ThreadCallback.h"
#include "ThreadsManager.h"
#include "RectangleDB.h"
#include "DB.h"
#include "Chromosome.h"
#include "Utils.h"

#include "wx/wx.h"

#include <ctime>

class Threadable;
class RectangleDrawer;
class Population;

class MainController : public ThreadCallback
{
public:
	MainController(RectangleDrawer*);
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
	clock_t				m_Start, m_End;

	ThreadsManager		m_ThreadManager;
	RectangleDrawer*	m_pRectangleDrawer;

	Population*			m_pPopulation;
	bool				m_bTimeStarted;

	static size_t		s_iCurrentIterationCount;

};

template<typename T>
void MainController::DoRun(T* pClass)
{
	wxLogDebug("MainController::DoRun iteration = %d", s_iCurrentIterationCount);

	if (s_iCurrentIterationCount == 0 && !m_bTimeStarted)
	{
		m_bTimeStarted = true;
		m_Start = clock();
	}
	else if (s_iCurrentIterationCount == ITERATION_COUNT)
	{
		m_End = clock();
		double time = (double)(m_End - m_Start) / CLOCKS_PER_SEC;
		if (m_pPopulation->GetChromosomes().size() > 0)
		{
			m_pRectangleDrawer->Draw((*(m_pPopulation->GetChromosomes().begin()))->GetRectangleDB(), time);
		}
		DB::CleanDB();

		s_iCurrentIterationCount = 0;
		m_bTimeStarted = false;
		return;
	}
	if (m_CurrentState == NONE)
		m_CurrentState = PLACEMENT;

	m_ThreadManager.Register(this);
	m_ThreadManager.Run(pClass, m_pPopulation);
}
