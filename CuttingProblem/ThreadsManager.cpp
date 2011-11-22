#include "ThreadsManager.h"

#include "Utils.h"
#include "ICrossingover.h"
#include "Threadable.h"

ThreadsManager::ThreadsManager(void)
: m_pCallback(NULL)
{
}


ThreadsManager::~ThreadsManager(void)
{
}

void ThreadsManager::Run( /*Threadable* pThread */)
{
	ICrossingover* pThread = NULL;

	for (size_t i = 0; i < THREAD_COUNT; ++i)
	{
		pThread = new ICrossingover;
		pThread->Register(this);
		pThread->Create();
		pThread->Run();
	}
}

void ThreadsManager::OnThreadsFinish()
{
	wxLogDebug("ThreadsManager::OnThreadsFinish called");
	if (m_pCallback)
		m_pCallback->OnThreadsFinish();
}
