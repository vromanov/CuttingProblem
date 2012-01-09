#include "IMutator.h"

#include "Population.h"
#include "Chromosome.h"

#include "wx/wx.h"

IMutator::IMutator( Population* pPopulation )
: m_pPopulation(pPopulation)
{
	return;
}

IMutator::~IMutator()
{
	return;
}

void IMutator::DoEntry(void)
{
	wxLogDebug("TRACE: IMutator::DoEntry called");

	const size_t POPULATION_SIZE = m_pPopulation->GetChromosomes().size();

	/**/
	while (s_iChromosomeIndex < POPULATION_SIZE)
	{
		s_CriticalSection.Enter();

		if (s_iChromosomeIndex >= POPULATION_SIZE)
		{
			s_CriticalSection.Leave();
			break;
		}

		Chromosome* pChromosome = m_pPopulation->GetChromosomes()[s_iChromosomeIndex++];
		s_CriticalSection.Leave();

		DoMutator(pChromosome);
		pChromosome->ReInitDB();
	}
}

void IMutator::DoExit(void)
{
	wxLogDebug("TRACE: IMutator::DoExit called");
	s_iChromosomeIndex = 0;
}

size_t IMutator::s_iChromosomeIndex = 0;