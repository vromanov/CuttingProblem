#include "MainController.h"

#include "ICrossingover.h"

#include <vector>

int MainController::s_iRunCount = 0;

MainController::MainController(void)
: m_CurrentState(NONE)
{
}


MainController::~MainController(void)
{
}


void MainController::Run()
{
	wxLogDebug("MainController::Run called");

	if (s_iRunCount == 0)
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
		m_CurrentState = PLACEMENT;

	m_ThreadManager.Register(this);
	m_ThreadManager.Run(/*NULL*/);
}

void MainController::OnThreadsFinish()
{
	m_CriticalSection.Enter();
	switch(m_CurrentState)
	{
	case CROSSINGOVER:
		wxLogDebug ("OnThreadsFinish. state == CROSSINGOVER");
		m_CurrentState = MUTATOR;
		Run();
		break;
	case MUTATOR:
		wxLogDebug ("OnThreadsFinish. state == MUTATOR");
		m_CurrentState = SELECTOR;
		Run();
		break;
	case SELECTOR:
		wxLogDebug ("OnThreadsFinish. state == SELECTOR");
		++s_iRunCount;
		m_CurrentState = NONE;
		Run();
		break;
	case PLACEMENT:
		wxLogDebug ("OnThreadsFinish. state == PLACEMENT");
		m_CurrentState = CROSSINGOVER;
		Run();
		break;
	default:
		break;
	}
	m_CriticalSection.Leave();
}
