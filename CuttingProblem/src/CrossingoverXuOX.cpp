#include "CrossingoverXuOX.h"

#include "Population.h"
#include "Chromosome.h"
#include "RectangleF.h"
#include "RectangleDB.h"
#include "FieldController.h"
#include "Segment.h"

#include "wx/wx.h"

CrossingoverXuOX::CrossingoverXuOX(Population* population)
: CrossingoverOX(population)
{
}


CrossingoverXuOX::~CrossingoverXuOX(void)
{
}

size_t CrossingoverXuOX::GetCrossPoint( Chromosome* pParent )
{
	FieldController fieldCtrl;
	size_t crossPoint = fieldCtrl.FindBigestHolePosition(pParent->GetRectangleDB());

	if (crossPoint > 0)
		return crossPoint - 1;

	// if holes don't exists we get rand cross point
	size_t chromosomeSize = pParent->Size();
	while (crossPoint == 0 || crossPoint == chromosomeSize)
	{
		crossPoint = rand() % chromosomeSize;
		wxLogDebug("crossPoint == 0 || crossPoint == chromosomeSize");
	}

	return crossPoint;
}
