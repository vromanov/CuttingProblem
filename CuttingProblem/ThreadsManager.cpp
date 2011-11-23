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



void ThreadsManager::OnThreadsFinish()
{
	wxLogDebug("ThreadsManager::OnThreadsFinish called");
	if (m_pCallback)
		m_pCallback->OnThreadsFinish();
}
