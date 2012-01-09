#include "UpPointFitness.h"
#include "IFitness.h"
#include "Population.h"
#include "Chromosome.h"
#include "RectangleF.h"

UpPointFitness::UpPointFitness( Population* pPopulation ) 
: IFitness(pPopulation)
{
	return;
}


UpPointFitness::~UpPointFitness(void)
{
	return;
}

void UpPointFitness::DoEntry(void)
{
	//wxLogDebug("TRACE: UpPointFitness::DoEntry called");

	while (s_iChromosomeIndex < m_pPopulation->GetChromosomes().size())
	{
		s_CriticalSection.Enter();
		if (s_iChromosomeIndex >= m_pPopulation->GetChromosomes().size())
		{
			s_CriticalSection.Leave();
			continue;
		}
		Chromosome* pChromosome = m_pPopulation->GetChromosomes()[s_iChromosomeIndex];
		++s_iChromosomeIndex;
		s_CriticalSection.Leave();

		if (!pChromosome->IsPlacement())
		{
			wxLogDebug("UpPointFitness::DoEntry pChromosome is NOT placement");
			continue;
		}

		float fFitnessValue = pChromosome->FitnessValue();

		if (fFitnessValue != -1.f)
		{
			wxLogDebug("WARNING: UpPointFitness::DoEntry Fitness value already calculated");
			continue;
		}

		for (size_t i = 0, i_end = pChromosome->Size(); i < i_end; ++i)
		{
			RectangleF* pRectangle = pChromosome->GetRectangle(pChromosome->GetGene(i));
			float fTempFitnessValue = pRectangle->GetTopLeft().Y();
			if (fTempFitnessValue < fFitnessValue || fFitnessValue == -1)
				fFitnessValue = fTempFitnessValue;
		}

		pChromosome->FitnessValue() = fFitnessValue;
	}
}

void UpPointFitness::DoExit(void)
{
	wxLogDebug("TRACE: UpPointFitness::DoExit called");
	s_iChromosomeIndex = 0;
}

size_t UpPointFitness::s_iChromosomeIndex = 0;
