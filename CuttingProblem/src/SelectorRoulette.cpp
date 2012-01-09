#include "SelectorRoulette.h"
#include "Population.h"
#include "Chromosome.h"
#include "Utils.h"

#include "wx/wx.h"

#include <algorithm>

SelectorRoulette::SelectorRoulette(Population* population)
: ISelector(population)
{
	return;
}

SelectorRoulette::~SelectorRoulette(void)
{
	return;
}

bool SortChromosomeByProbabilityValue(Chromosome* pChr0, Chromosome* pChr1)
{
	return pChr0->ProbabilityValue() > pChr1->ProbabilityValue();
}

void SelectorRoulette::DoEntry( void )
{
	s_CriticalSection.Enter();

	if (!bIsDone) // only one thread will be in critical section
	{
		bIsDone = true;

		// do something in one thread

		// calculate general population fitness value
		float fSummFitness = 0;
		for (size_t i = 0, i_end = m_pPopulation->GetChromosomes().size(); i < i_end; ++i)
		{
			Chromosome* pChromosome = m_pPopulation->GetChromosome(i);
			fSummFitness += pChromosome->FitnessValue();
		}

		// calculate probability value of each chromosome
		for (size_t i = 0, i_end = m_pPopulation->GetChromosomes().size(); i < i_end; ++i)
		{
			Chromosome* pChromosome = m_pPopulation->GetChromosome(i);
			pChromosome->ProbabilityValue() = pChromosome->FitnessValue() / fSummFitness * i_end;
		}

		size_t populationSize = m_pPopulation->GetChromosomes().size();

		// add chromosome which probability greater than 1
		for (size_t i = 0; i < populationSize; ++i)
		{
			Chromosome* pChromosome = m_pPopulation->GetChromosome(i);
			if (pChromosome->ProbabilityValue() >= 1.f)
				m_pPopulation->GetChromosomes().push_back(new Chromosome(*pChromosome)); // add to the end of population
		}

		std::sort(m_pPopulation->GetChromosomes().begin(), m_pPopulation->GetChromosomes().end(), SortChromosomeByProbabilityValue);

		// delete unnecessary chromosomes
		while (populationSize != m_pPopulation->GetChromosomes().size())
		{
			delete m_pPopulation->GetChromosomes().back();
			m_pPopulation->GetChromosomes().pop_back();
		}
	}

	s_CriticalSection.Leave();
}

void SelectorRoulette::DoExit( void )
{
	wxLogDebug("TRACE: SelectorRoulette::DoExit called");
	bIsDone = false;
}

bool SelectorRoulette::bIsDone = false;