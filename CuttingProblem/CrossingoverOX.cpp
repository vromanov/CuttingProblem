#include "CrossingoverOX.h"

#include "Chromosome.h"

#include "wx/wx.h"

CrossingoverOX::CrossingoverOX( Population* pPopulation )
: ICrossingover(pPopulation)
{

}

CrossingoverOX::~CrossingoverOX()
{

}

size_t CrossingoverOX::GetCrossPoint(size_t chromosomeSize)
{
	size_t crossPoint = rand() % chromosomeSize;

	while (crossPoint < 1 || crossPoint == chromosomeSize - 1)
	{
		crossPoint = rand() % chromosomeSize;
	}

	return crossPoint;
}

Chromosome* CrossingoverOX::DoCrossingover( Chromosome* pParent0, Chromosome* pParent1 )
{
	//wxLogDebug("CrossingoveOX::DoCrossingover called");

	const size_t CHROMOSOME_SIZE = pParent0->Size();
	const size_t FIRST_PART = GetCrossPoint(CHROMOSOME_SIZE);

	Chromosome* pChild = new Chromosome(CHROMOSOME_SIZE);

	for (size_t i = 0, i_end = FIRST_PART; i < i_end; ++i)
		pChild->SetGene(i, pParent0->GetGene(i));

	size_t next = FIRST_PART;
	bool willAdded = true;

	for (size_t i = 0, i_end = CHROMOSOME_SIZE; i < i_end; ++i)
	{
		// set flag for " add to child"
		willAdded = true;

		// try to find this elem in child
		for (size_t j = 0; j < FIRST_PART; ++j)
		{
			// if found set flag for "don't add to child"
			if (pChild->GetGene(j) == pParent1->GetGene(i))
			{
				willAdded = false;
				break;
			}
		}

		// don't add to child
		if (!willAdded)
			continue;

		// else if elem don't found 
		// we're adding it to child
		pChild->SetGene(next, pParent1->GetGene(i));
		++next;
	}

	return pChild;
}


