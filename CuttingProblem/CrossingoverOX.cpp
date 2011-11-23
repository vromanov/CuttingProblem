#include "CrossingoverOX.h"

float CrossingoveOX::j = 1;

CrossingoveOX::CrossingoveOX()
{

}

CrossingoveOX::~CrossingoveOX()
{

}

void CrossingoveOX::DoEntry( void )
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
}

void CrossingoveOX::DoExit( void )
{
	j = 1;
}