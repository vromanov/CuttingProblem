#include "Reblocker.h"

#include "Population.h"
#include "Chromosome.h"

#include "RectangleF.h"

#include "wx/wx.h"

Reblocker::Reblocker( Population* pPopulation )
: m_pPopulation(pPopulation)
{
	return;
}

Reblocker::~Reblocker()
{
	return;
}

void Reblocker::DoEntry(void)
{
	wxLogDebug("TRACE: Reblocker::DoEntry called");

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

		while (DoReblock(pChromosome)) {}
		pChromosome->WipeDB();
	}
}

void Reblocker::DoExit(void)
{
	wxLogDebug("TRACE: Reblocker::DoExit called");
	s_iChromosomeIndex = 0;
}

bool Reblocker::DoReblock(Chromosome* pChromosome)
{
	for (int i = 0, i_end = pChromosome->Size(); i < i_end; ++i)
	{
		RectangleF* pRectangle0 = pChromosome->GetRectangle(pChromosome->GetGene(i));
		for (int j = i+1, j_end = pChromosome->Size(); j < j_end; ++j)
		{
			RectangleF* pRectangle1 = pChromosome->GetRectangle(pChromosome->GetGene(j));

			if (CheckHorizontalOneSide(pRectangle1, pRectangle0))
			{
				pRectangle1->Enlarge(pRectangle0);

				pChromosome->DeleteRectangle(pChromosome->GetGene(i));
				pChromosome->DeleteGene(i);
				return true;
			}
			else
			if (CheckVerticalOneSide(pRectangle0, pRectangle1))
			{
				pRectangle1->Enlarge(pRectangle0);

				pChromosome->DeleteRectangle(pChromosome->GetGene(i));
				pChromosome->DeleteGene(i);
				return true;
			}

		}
	}
	return false;
}


bool Reblocker::CheckHorizontalOneSide(RectangleF* pRec0, RectangleF* pRec1)
{
	return 
		((pRec0->GetBottomRight().X() == pRec1->GetTopLeft().X()) && 
		(pRec0->GetBottomRight().Y() == pRec1->GetBottomRight().Y()) &&
		(pRec0->GetBottomRight().X() == pRec1->GetTopLeft().X()) &&
		(pRec0->GetTopLeft().Y() == pRec1->GetTopLeft().Y()));
}

bool Reblocker::CheckVerticalOneSide(RectangleF* pRec0, RectangleF* pRec1)
{
	return 
		((pRec0->GetBottomRight().X() == pRec1->GetBottomRight().X()) && 
		(pRec0->GetTopLeft().X() == pRec1->GetTopLeft().X()) &&
		(pRec0->GetTopLeft().Y() == pRec1->GetBottomRight().Y()));
}

size_t Reblocker::s_iChromosomeIndex = 0;