#include "MainController.h"

#include "CrossingoverOX.h"

#include <vector>

int MainController::s_iRunCount = 0;

MainController::MainController(void)
: m_CurrentState(NONE)
{
	return;
}


MainController::~MainController(void)
{
	return;
}


void MainController::OnThreadsFinish()
{
	m_CriticalSection.Enter();
	
	CrossingoveOX* pCrossingover = NULL;

	switch(m_CurrentState)
	{
	case CROSSINGOVER:
		wxLogDebug ("OnThreadsFinish. state == CROSSINGOVER");
		m_CurrentState = MUTATOR;
		DoRun(pCrossingover);
		break;
	case MUTATOR:
		wxLogDebug ("OnThreadsFinish. state == MUTATOR");
		m_CurrentState = SELECTOR;
		DoRun(pCrossingover);
		break;
	case SELECTOR:
		wxLogDebug ("OnThreadsFinish. state == SELECTOR");
		++s_iRunCount;
		m_CurrentState = NONE;
		DoRun(pCrossingover);
		break;
	case PLACEMENT:
		wxLogDebug ("OnThreadsFinish. state == PLACEMENT");
		m_CurrentState = CROSSINGOVER;
		DoRun(pCrossingover);
		break;
	default:
		break;
	}
	m_CriticalSection.Leave();
}

void MainController::Run()
{
	wxLogDebug("MainController::Run called");

	CrossingoveOX* pCrossingover = NULL;
	DoRun(pCrossingover);
}
