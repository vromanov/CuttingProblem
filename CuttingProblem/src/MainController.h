#pragma once

#include "ThreadCallback.h"
#include "ThreadsManager.h"
#include "RectangleDB.h"
#include "DB.h"
#include "Chromosome.h"
#include "Utils.h"

#include "wx/wx.h"

#include <ctime>
#include <vector>

class Threadable;
class RectangleDrawer;
class Population;

class MainController : public ThreadCallback
{
public:
	MainController(RectangleDrawer*);
	~MainController(void);
	
	void				Run();


	// TODO: Move to stats class
	Chromosome*			GetBestChromosome() {return m_pBestChromosome;}
	size_t				GetCurrentTestConfig() { return m_uiCurrentTestConfig; }
	size_t				GetCurrentTestRepeat() { return m_uiCurrentTestRepeat; }
	
private:
	
	template<typename T>
	void				DoRun(T* pClass);
	void				RunState(const char* pName);
	void				RunTest(const char* testName);

	virtual void		OnThreadsFinish();
	
	clock_t				m_Start, m_End;

	ThreadsManager		m_ThreadManager;
	RectangleDrawer*	m_pRectangleDrawer;

	Population*			m_pPopulation;
	bool				m_bTimeStarted;
	
	std::vector<std::string>	m_StateQueue;
	size_t						m_uiCurrentState;

	std::vector<std::string>	m_TestFiles;
	std::vector<std::string>	m_TestConfigs;
	size_t						m_uiTestRepeat;
	
	size_t						m_uiCurrentTestFile;
	size_t						m_uiCurrentTestConfig;
	size_t						m_uiCurrentTestRepeat;

	Chromosome*					m_pBestChromosome;

	static size_t				s_iCurrentIterationCount;
	static wxCriticalSection	s_CriticalSection;

};

template<typename T>
void MainController::DoRun(T* pClass)
{
	wxLogDebug("MainController::DoRun iteration = %d", s_iCurrentIterationCount);

	const size_t ITERATION_COUNT = ConfigReader::GetInstance()->GetConfigIntValue("GENERAL_POPULATION_COUNT");

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
			m_pBestChromosome = *(m_pPopulation->GetChromosomes().begin());
			m_pRectangleDrawer->Draw(this, time);
		}
		DB::CleanDB();

		s_iCurrentIterationCount = 0;
		m_bTimeStarted = false;
		Run();
		return;
	}

	m_ThreadManager.Register(this);
	m_ThreadManager.Run(pClass, m_pPopulation);
}
