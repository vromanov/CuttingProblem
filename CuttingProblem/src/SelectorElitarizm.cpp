#include "SelectorElitarizm.h"
#include "Population.h"
#include "Chromosome.h"
#include "Utils.h"
#include "ConfigReader.h"

#include "wx/wx.h"

#include <algorithm>

SelectorElitarizm::SelectorElitarizm(Population* population)
    : ISelector(population)
{
    return;
}

SelectorElitarizm::~SelectorElitarizm(void)
{
    return;
}

bool SortChromosomeByFitnessValue(Chromosome* pChr0, Chromosome* pChr1)
{
	return pChr0->FitnessValue() > pChr1->FitnessValue();
}

void SelectorElitarizm::DoEntry( void )
{
	s_CriticalSection.Enter();

	if (!bIsDone) // only one thread will be in critical section
	{
		bIsDone = true;

		// do something in one thread
		std::sort(m_pPopulation->GetChromosomes().begin(), m_pPopulation->GetChromosomes().end(), SortChromosomeByFitnessValue);

		const size_t CHROMOSOME_BEST_COUNT = ConfigReader::GetInstance()->GetFileConfigIntValue("BEST_CHROMOSOMES");
		for (size_t i = CHROMOSOME_BEST_COUNT, i_end = m_pPopulation->GetChromosomes().size(); i < i_end; ++i)
		{
			// delete unnecessary chromosomes
			Chromosome* pChromosome = m_pPopulation->GetChromosome(i);
			delete pChromosome;
		
			// add new chromosomes
			pChromosome = Chromosome::GenerateRandChromosome();
			m_pPopulation->AddChromosome(i, pChromosome);

			pChromosome = NULL;
		}
	}

	s_CriticalSection.Leave();
}

void SelectorElitarizm::DoExit( void )
{
	wxLogDebug("TRACE: SelectorElitarizm::DoExit called");
	bIsDone = false;
}

bool SelectorElitarizm::bIsDone = false;