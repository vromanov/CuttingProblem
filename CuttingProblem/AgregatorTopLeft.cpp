#include "AgregatorTopLeft.h"

#include "Population.h"
#include "Chromosome.h"
#include "RectangleF.h"
#include "FieldController.h"
#include "RectangleDrawer.h"

#include <vector>

AgregatorTopLeft::AgregatorTopLeft(Population* pPopulation)
: m_pPopulation(pPopulation)
{
}

AgregatorTopLeft::~AgregatorTopLeft()
{
	m_pPopulation = NULL;
}

void AgregatorTopLeft::DoEntry( void )
{
	//wxLogDebug("AgregatorTopLeft::DoEntry called");

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

		if (pChromosome->IsPlacement())
		{
			wxLogDebug("AgregatorTopLeft::DoEntry pChromosome is placement");
			continue;
		}

		for (size_t i = 0, i_end = pChromosome->Size(); i < i_end; ++i)
		{
			RectangleF* pRectangle = pChromosome->GetRectangle(pChromosome->GetGene(i));
			if (pRectangle->GetStatus() == FREE)
			{
				pRectangle->SetPosition(pRectangle->GetBottomRight());
				SetRectangleOnField(pRectangle, pChromosome->GetRectangleDB());
				pRectangle->SetStatus(ON_FIELD);
			}
		}

		pChromosome->SetPlacement(true);
	}
}

void AgregatorTopLeft::DoExit( void )
{
	s_iChromosomeIndex = 0;
}


void AgregatorTopLeft::SetRectangleOnField(RectangleF* pRectangle, const RectangleDB& rectangleDB)
{
	//ConfigWrap& config = ConfigWrap::GetInstance();
	//int HEIGHT = config.CanvasHeight(), WIDTH = config.CanvasWidth();	
	//int VERTICAL_DIRECTION = 1, HORIZONTAL_DIRECTION = 0;

	int HEIGHT = 50, WIDTH = 20;	

	// STEP 0: initialize left model position
	float leftLimitPos = 0;

	while (true)
	{
		// find closest down model
		Vector2F currentModelPosition = pRectangle->GetPosition();
		Vector2F newModelPosition = currentModelPosition;
	
		FieldController modelCtrl;
		const RectangleF* pClosestDownModel = modelCtrl.FindClosestRectangles(pRectangle, rectangleDB, VERTICAL_DIRECTION);
		
		// try to move down
		if (!pClosestDownModel)
		{
			newModelPosition.Y() = HEIGHT - pRectangle->GetDimension().Y();
		}
		else
		{
			newModelPosition.Y() = pClosestDownModel->GetTopLeft().Y() - pRectangle->GetDimension().Y();
		}

		if (newModelPosition != currentModelPosition)
		{
			// move to calculated position
			pRectangle->SetPosition(newModelPosition);

			// calculate the max possible left position of model
			FieldController modelCtrl;
			const RectangleF* pClosestLeftModel = modelCtrl.FindClosestRectangles(pRectangle, rectangleDB, HORIZONTAL_DIRECTION);

			if (!pClosestLeftModel)
			{
				leftLimitPos = WIDTH - pRectangle->GetDimension().X();
			}
			else
			{
				// we are interested only right position closest model
				if (pClosestLeftModel->GetTopLeft().X() < pRectangle->GetTopLeft().X())
				{
					leftLimitPos = WIDTH - pRectangle->GetDimension().X();
					pClosestLeftModel = NULL;
				}
				else
				{
					leftLimitPos = pClosestLeftModel->GetTopLeft().X() - pRectangle->GetDimension().X();
				}
			}
		}


		// try to move left
		if (!pClosestDownModel)
		{
			newModelPosition.X() = leftLimitPos;
			pRectangle->SetPosition(newModelPosition);
			return;
		}

		newModelPosition.X() = pClosestDownModel->GetBottomRight().X() + pRectangle->GetDimension().X();

		if (newModelPosition.X() > leftLimitPos)
		{
			newModelPosition.X() = leftLimitPos;

			pRectangle->SetPosition(newModelPosition);
			return;
		}

		// if cannot any move then return
		if (newModelPosition == currentModelPosition)
			return;

		// move to calculated position
		pRectangle->SetPosition(newModelPosition);
	}

}

size_t AgregatorTopLeft::s_iChromosomeIndex = 0;
