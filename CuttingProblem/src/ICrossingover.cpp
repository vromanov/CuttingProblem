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

void ICrossingover::DoEntry( void )
{
/**/
	srand(time(NULL));

	const size_t POPULATION_SIZE = m_pPopulation->GetChromosomes().size();

	if (POPULATION_SIZE < 2)
		return;

	if (!s_pNewPopulation)
		s_pNewPopulation = new Population(POPULATION_SIZE);

/**/
    while (s_iChromosomeIndex < POPULATION_SIZE - 1)
	{
		s_CriticalSection.Enter();

		if (s_iChromosomeIndex >= POPULATION_SIZE - 1)
		{
			s_CriticalSection.Leave();
			continue;
		}

		IndexedChromosome parent0;
		parent0.uiPosition = s_iChromosomeIndex;
		parent0.pChromosome = m_pPopulation->GetChromosomes()[s_iChromosomeIndex];
		
		++s_iChromosomeIndex;
		
		IndexedChromosome parent1;
		parent1.uiPosition = s_iChromosomeIndex;
		parent1.pChromosome = m_pPopulation->GetChromosomes()[s_iChromosomeIndex];

		++s_iChromosomeIndex;

		s_CriticalSection.Leave();

		IndexedChromosome child0;
		child0.uiPosition = parent0.uiPosition;
		child0.pChromosome = DoCrossingover(parent0.pChromosome, parent1.pChromosome);

		IndexedChromosome child1;
		child1.uiPosition = parent1.uiPosition;
		child1.pChromosome = DoCrossingover(parent1.pChromosome, parent0.pChromosome);

		s_CriticalSection.Enter();
		
		s_pNewPopulation->AddChromosome(child0.uiPosition, child0.pChromosome);
		s_pNewPopulation->AddChromosome(child1.uiPosition, child1.pChromosome);
		
		s_CriticalSection.Leave();
	}

/**
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

	m_pPopulation->Clear();

	size_t size = s_pNewPopulation->GetChromosomes().size();
	m_pPopulation->GetChromosomes().resize(size);
	for (size_t i = 0; i < size; ++i)
	{
		m_pPopulation->AddChromosome(i, s_pNewPopulation->GetChromosome(i));
	}

	delete s_pNewPopulation;
	s_pNewPopulation = NULL;

	//m_pPopulation->Clear();
	//*m_pPopulation = *s_pNewPopulation;
	//s_pNewPopulation->Clear();
}


size_t ICrossingover::s_iChromosomeIndex = 0;
Population*	ICrossingover::s_pNewPopulation = NULL;