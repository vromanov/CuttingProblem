#include "CrossingoverPMX.h"

#include "Chromosome.h"

#include "wx/wx.h"

CrossingoverPMX::CrossingoverPMX(Population* population) : ICrossingover(population)
{
}


CrossingoverPMX::~CrossingoverPMX(void)
{
}

Chromosome* CrossingoverPMX::DoCrossingover( Chromosome* pParent0, Chromosome* pParent1 )
{

	const size_t CHROMOSOME_SIZE = pParent0->Size();

	Chromosome* pChild = new Chromosome(CHROMOSOME_SIZE);


	size_t pos0 = rand() % CHROMOSOME_SIZE;
	size_t pos1 = rand() % CHROMOSOME_SIZE;

	while (pos0 == 0 || pos0 == CHROMOSOME_SIZE - 1 ||
		pos1 == 0 || pos1 == CHROMOSOME_SIZE - 1 ||
		pos1 == pos0)
	{
		pos0 = rand() % CHROMOSOME_SIZE;
		pos1 = rand() % CHROMOSOME_SIZE;
	}
	
	if (pos0 > pos1)
	{
		size_t tmpPos = pos0;
		pos0 = pos1;
		pos1 = tmpPos;
	}


	for (size_t i = 0; i < CHROMOSOME_SIZE; ++i)
	{
		if (i >= pos0 && i <=pos1)
			pChild->SetGene(i, pParent1->GetGene(i));
		else
			pChild->SetGene(i, pParent0->GetGene(i));
	}

	int genePositionInParent1 = -1;


	bool isChildFinished = false;
	while (!isChildFinished)
	{
		isChildFinished = true;
		for (size_t i = 0; i < CHROMOSOME_SIZE; ++i)
		{
			size_t pos = findSameGene(pChild->GetGene(i), *pChild, pos0, pos1);

			if (pos != -1)
			{
				isChildFinished = false;
				// search gene position in parent1
				for (size_t j = 0; j < CHROMOSOME_SIZE; ++j)
				{
					if(pParent1->GetGene(j) == pChild->GetGene(pos))
					{
						genePositionInParent1 = j;
						break;
					}
				}

				// insert in child from parent 0
				pChild->SetGene(pos, pParent0->GetGene(genePositionInParent1));

			}
		}
	}

	return pChild;
 }

int CrossingoverPMX::findSameGene( const int& gene, const Chromosome& chromosome, int pos0, int pos1 )
{
	int resultPosition = -1;
	int geneCount = 0;
	for(int i = 0, i_end = chromosome.Size(); i < i_end; ++i)
	{
		if (chromosome.GetGene(i) == gene)
		{
			if (!(i >= pos0 && i <= pos1))
				resultPosition = i;
			++geneCount;
			if (geneCount >= 2)
			{
				if (resultPosition != -1)
					return resultPosition;
				else
					return i;
			}

		}
	}
	return -1;
}
