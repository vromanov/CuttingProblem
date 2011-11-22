#pragma once

#include "ThreadCallback.h"

class Threadable;

class ThreadsManager : public ThreadCallback
{
public:
	ThreadsManager(void);
	~ThreadsManager(void);

	void	Run(/*Threadable* pThread*/);
	void	OnThreadsFinish();

	void	Register(ThreadCallback* pCallBack) { m_pCallback = pCallBack; }
private:
	ThreadCallback* m_pCallback;
};

