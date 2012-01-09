#include "MainController.h"

#include "AgregatorTopLeft.h"

#include "CrossingoverOX.h"
#include "CrossingoverPMX.h"
#include "CrossingoverXuOX.h"

#include "UpPointFitness.h"

#include "MutatorInsert.h"
#include "MutatorChange.h"
#include "MutatorXuInsert.h"

#include "SelectorElitarizm.h"
#include "SelectorRoulette.h"

#include "RectangleDB.h"
#include "RectangleF.h"
#include "RectangleDrawer.h"

#include "Chromosome.h"
#include "Population.h"

#include <vector>

MainController::MainController(RectangleDrawer* pRectangleDrawer)
: m_pRectangleDrawer(pRectangleDrawer)
, m_pPopulation(NULL)
, m_bTimeStarted(false)
, m_uiCurrentState(0)
{
	//m_StateQueue.push_back("OX");
	//m_StateQueue.push_back("PMX");
	
	//m_StateQueue.push_back("Change");
	m_StateQueue.push_back("TopLeft");
	m_StateQueue.push_back("XuOX");

	m_StateQueue.push_back("TopLeft");
	m_StateQueue.push_back("XuInsert");

	m_StateQueue.push_back("TopLeft");
	m_StateQueue.push_back("UpPoint");

	m_StateQueue.push_back("Roulette");

	//m_StateQueue.push_back("Insert");
	//m_StateQueue.push_back("Change");

	//m_StateQueue.push_back("TopLeft");

	//m_StateQueue.push_back("UpPoint");

	//m_StateQueue.push_back("Roulette");
	//m_StateQueue.push_back("TopLeft");
	//m_StateQueue.push_back("UpPoint");
}


MainController::~MainController(void)
{
	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
	}
}


void MainController::OnThreadsFinish()
{
	s_CriticalSection.Enter();

	RunStep(m_StateQueue[m_uiCurrentState++]);

	if (m_uiCurrentState >= m_StateQueue.size())
	{
		m_uiCurrentState = 0;
		++s_iCurrentIterationCount;
	}

	s_CriticalSection.Leave();
}

void MainController::RunStep(const char* pName)
{
	void* pT = NULL;
	if (strcmp(pName, "OX") == 0)
		DoRun((CrossingoverOX*)pT);
	else if (strcmp(pName, "PMX") == 0)
		DoRun((CrossingoverPMX*)pT);
	else if (strcmp(pName, "XuOX") == 0)
		DoRun((CrossingoverXuOX*)pT);
	else if (strcmp(pName, "Insert") == 0)
		DoRun((MutatorInsert*)pT);
	else if (strcmp(pName, "Change") == 0)
		DoRun((MutatorChange*)pT);
	else if (strcmp(pName, "XuInsert") == 0)
		DoRun((MutatorXuInsert*)pT);
	else if (strcmp(pName, "TopLeft") == 0)
		DoRun((AgregatorTopLeft*)pT);
	else if (strcmp(pName, "UpPoint") == 0)
		DoRun((UpPointFitness*)pT);
	else if (strcmp(pName, "Elitarizm") == 0)
		DoRun((SelectorElitarizm*)pT);
	else if (strcmp(pName, "Roulette") == 0)
		DoRun((SelectorRoulette*)pT);
}

void MainController::Run()
{
	wxLogDebug("MainController::Run called");

	m_uiCurrentState = 0;
	s_iCurrentIterationCount = 0;

	DB::CreateDB("tests/test.txt");

	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
	}
	m_pPopulation = Population::GenerateRandPopulation(CHROMOSOME_COUNT);

	OnThreadsFinish();
}

size_t MainController::s_iCurrentIterationCount = 0;
wxCriticalSection	MainController::s_CriticalSection;
