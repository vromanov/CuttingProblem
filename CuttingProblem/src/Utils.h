#pragma once

#include "wx/thread.h"

const size_t	THREAD_COUNT = wxThread::GetCPUCount();
const size_t	ITERATION_COUNT = 10;
const size_t	CHROMOSOME_COUNT = 10;
const size_t	CHROMOSOME_BEST_COUNT = 1;

const size_t	HEIGHT = 200;
const size_t	WIDTH = 80;	

const size_t	SCALING_COEFF = 3;
const size_t	SHIFT = 30;
