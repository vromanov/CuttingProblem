#include "Threadable.h"

#include "ThreadCallback.h"

Threadable::Threadable() : m_pCallback(NULL)
{

}

Threadable::~Threadable()
{

}

void* Threadable::Entry( void )
{
	DoEntry();
	
	s_CriticalSection.Enter();
	++s_iCurrentThread;
	if (s_iCurrentThread == THREAD_COUNT)
	{
		s_iCurrentThread = 0;
		DoExit();
		if (m_pCallback)
			m_pCallback->OnThreadsFinish();
	}
	s_CriticalSection.Leave();
	return NULL;
}

void Threadable::OnExit()
{
	if (s_iCurrentThread == THREAD_COUNT)
		DoExit();
}

void Threadable::Register( ThreadCallback* pCallback )
{
	m_pCallback = pCallback;
}

size_t Threadable::s_iCurrentThread = 0;
wxCriticalSection	Threadable::s_CriticalSection;
