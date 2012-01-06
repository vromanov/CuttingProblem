#pragma once

#include "ThreadCallback.h"

class Threadable;
class Population;

class ThreadsManager : public ThreadCallback
{
public:
	ThreadsManager(void);
	~ThreadsManager(void);

	template<typename T>
	void Run(T* pThread, Population* pPopulation)
	{
		for (size_t i = 0; i < THREAD_COUNT; ++i)
		{
			pThread = new T(pPopulation);
			pThread->Register(this);
			pThread->Create();
			pThread->Run();
		}
	}

	void	OnThreadsFinish();

	void	Register(ThreadCallback* pCallBack) { m_pCallback = pCallBack; }
private:
	ThreadCallback* m_pCallback;
};

