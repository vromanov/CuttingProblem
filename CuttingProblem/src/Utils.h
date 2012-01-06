#pragma once

#include "wx/thread.h"

const size_t	THREAD_COUNT = wxThread::GetCPUCount();
const size_t	ITERATION_COUNT = 10;
const size_t	CHROMOSOME_COUNT = 10;