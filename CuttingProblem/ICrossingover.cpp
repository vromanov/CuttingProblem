#include "ICrossingover.h"

float ICrossingover::j = 1;

void ICrossingover::DoEntry( void )
{
	z = 1000;
	wxLogDebug("ICrossingover::DoEntry called");

	while (j < 1000)
	{
		m_CriticalSection.Enter();
		j += 0.1f;
		m_CriticalSection.Leave();

		for (float i = 1; i < 10000; i += 0.9f)
		{
			x = i;
			z /= x;
		}				
	}
	//j = 1;
}

void ICrossingover::DoExit()
{
	j = 1;
}
