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
#include "ConfigReader.h"

#include "Reblocker.h"

#include <vector>

MainController::MainController(RectangleDrawer* pRectangleDrawer)
: m_pRectangleDrawer(pRectangleDrawer)
, m_pPopulation(NULL)
, m_bTimeStarted(false)
, m_uiCurrentState(0)
, m_uiTestRepeat(0)

, m_uiCurrentTestFile(0)
, m_uiCurrentTestConfig(0)
, m_uiCurrentTestRepeat(0)
{
	ConfigReader::GetInstance()->LoadTestConfig("test.conf");

	m_TestFiles = ConfigReader::GetInstance()->GetTestPath();
	m_TestConfigs = ConfigReader::GetInstance()->GetTestConfigs();
	m_uiTestRepeat = ConfigReader::GetInstance()->GetTestRepeat();
}


MainController::~MainController(void)
{
	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
	}
	ConfigReader::DeleteInstance();
}


void MainController::OnThreadsFinish()
{
	s_CriticalSection.Enter();

	RunState(m_StateQueue[m_uiCurrentState++].c_str());

	if (m_uiCurrentState >= m_StateQueue.size())
	{
		m_uiCurrentState = 0;
		++s_iCurrentIterationCount;
	}

	s_CriticalSection.Leave();
}

void MainController::RunState(const char* pName)
{
	const char* pValue = ConfigReader::GetInstance()->GetConfigValue(pName).c_str();

	void* pT = NULL;
	if (strcmp(pValue, "OX") == 0)
		DoRun((CrossingoverOX*)pT);
	else if (strcmp(pValue, "PMX") == 0)
		DoRun((CrossingoverPMX*)pT);
	else if (strcmp(pValue, "XUOX") == 0)
		DoRun((CrossingoverXuOX*)pT);
	else if (strcmp(pValue, "INSERT") == 0)
		DoRun((MutatorInsert*)pT);
	else if (strcmp(pValue, "CHANGE") == 0)
		DoRun((MutatorChange*)pT);
	else if (strcmp(pValue, "XUINSERT") == 0)
		DoRun((MutatorXuInsert*)pT);
	else if (strcmp(pValue, "TOPLEFT") == 0)
		DoRun((AgregatorTopLeft*)pT);
	else if (strcmp(pValue, "UPPOINT") == 0)
		DoRun((UpPointFitness*)pT);
	else if (strcmp(pValue, "ELITARIZM") == 0)
		DoRun((SelectorElitarizm*)pT);
	else if (strcmp(pValue, "ROULETTE") == 0)
		DoRun((SelectorRoulette*)pT);
	else if (strcmp(pValue, "REBLOCK") == 0)
		DoRun((Reblocker*)pT);
}

void MainController::RunTest(const char* testName)
{
	ConfigReader::GetInstance()->SetCurrentTestFile(testName);
	DB::CreateDB(testName);

	m_uiCurrentState = 0;
	s_iCurrentIterationCount = 0;

	if (m_pPopulation)
	{
		m_pPopulation->Clear();
		delete m_pPopulation;
		m_pPopulation = NULL;
	}
	
	const char* pValue = ConfigReader::GetInstance()->GetConfigValue("GENERAL_CHROMOSOME_IN_POPULATION").c_str();
	const size_t CHROMOSOME_COUNT = atoi(pValue);

	m_pPopulation = Population::GenerateRandPopulation(CHROMOSOME_COUNT);

	OnThreadsFinish();
}

void MainController::Run()
{
	if (m_uiCurrentTestRepeat == m_uiTestRepeat)
	{
		m_uiCurrentTestRepeat = 0;

		if (m_uiCurrentTestConfig < m_TestConfigs.size() - 1)
		{
			++m_uiCurrentTestConfig;
		}
		else if (m_uiCurrentTestFile < m_TestFiles.size() - 1)
		{
			++m_uiCurrentTestFile;
			m_uiCurrentTestConfig = 0;
		}
		else
		{
			m_uiCurrentTestFile = 0;
			m_uiCurrentTestConfig = 0;
			m_uiCurrentTestRepeat = 0;			
			return;
		}
	}
	++m_uiCurrentTestRepeat;

	wxLogDebug("MainController::Run test");

	m_StateQueue = ConfigReader::GetInstance()->ReadConfig(m_TestConfigs[m_uiCurrentTestConfig].c_str());
	RunTest(m_TestFiles[m_uiCurrentTestFile].c_str());
}

size_t MainController::s_iCurrentIterationCount = 0;
wxCriticalSection	MainController::s_CriticalSection;
