#include "MainController.h"

#include "AgregatorTopLeft.h"
#include "CrossingoverOX.h"

#include "RectangleDB.h"
#include "RectangleF.h"
#include "RectangleDrawer.h"

#include "Chromosome.h"
#include "Population.h"

#include <vector>

size_t MainController::s_iCurrentIterationCount = 0;

MainController::MainController(RectangleDrawer* pRectangleDrawer)
	: m_CurrentState(NONE)
	, m_pRectangleDrawer(pRectangleDrawer)
	, m_pPopulation(NULL)
	, m_bTimeStarted(false)
{
	return;
}


MainController::~MainController(void)
{
	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
	}
	return;
}


void MainController::OnThreadsFinish()
{
	wxLogDebug ("OnThreadsFinish");

	m_CriticalSection.Enter();

	CrossingoverOX*		pCrossingover = NULL;
	AgregatorTopLeft*	pAgregator = NULL;

	switch(m_CurrentState)
	{
	case CROSSINGOVER:
		wxLogDebug ("OnThreadsFinish. state == CROSSINGOVER");
		++s_iCurrentIterationCount;
		m_CurrentState = PLACEMENT;
		DoRun(pCrossingover);
		break;
	case MUTATOR:
		wxLogDebug ("OnThreadsFinish. state == MUTATOR");
		m_CurrentState = SELECTOR;
		DoRun(pCrossingover);
		break;
	case SELECTOR:
		wxLogDebug ("OnThreadsFinish. state == SELECTOR");
		m_CurrentState = NONE;
		DoRun(pCrossingover);
		break;
	case PLACEMENT:
		wxLogDebug ("OnThreadsFinish. state == PLACEMENT");
		m_CurrentState = CROSSINGOVER;
		DoRun(pAgregator);
		break;
	default:
		break;
	}

	m_CriticalSection.Leave();
}

void MainController::Run()
{
	wxLogDebug("MainController::Run called");

	DB::CreateDB("tests/test.txt");

	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
	}
	m_pPopulation = Population::GenerateRandPopulation(CHROMOSOME_COUNT);


	m_CurrentState = PLACEMENT;
	OnThreadsFinish();
}
