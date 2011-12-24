#include "ICrossingover.h"

#include "Population.h"
#include "Chromosome.h"
#include "Utils.h"

#include "wx/wx.h"

ICrossingover::ICrossingover( Population* pPopulation )
	: m_pPopulation(pPopulation)
{

}

ICrossingover::~ICrossingover()
{

}

static size_t threadCount = 0;

void ICrossingover::DoEntry( void )
{

	return;
/**
	srand(time(NULL));

	const size_t POPULATION_SIZE = m_pPopulation->GetChromosomes().size();

	if (POPULATION_SIZE < 2)
		return;

	while (true)
	{
		m_CriticalSection.Enter();

		if (s_iChromosomeIndex >= POPULATION_SIZE - 2)
			break;

		Chromosome* pParent0 = m_pPopulation->GetChromosomes()[s_iChromosomeIndex++];
		Chromosome* pParent1 = m_pPopulation->GetChromosomes()[s_iChromosomeIndex++];

		m_CriticalSection.Leave();
		
		Chromosome* pChild0 = DoCrossingover(pParent0, pParent1);
		Chromosome* pChild1 = DoCrossingover(pParent1, pParent0);

		*pParent0 = *pChild0;
		*pParent1 = *pChild1;

		delete pChild0;
		delete pChild1;
	}
/**/
}

void ICrossingover::DoExit( void )
{
	s_iChromosomeIndex = 0;
}


size_t ICrossingover::s_iChromosomeIndex = 0;