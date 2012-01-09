#include "ISelector.h"

#include "Population.h"

#include "wx/wx.h"

ISelector::ISelector( Population* pPopulation )
: m_pPopulation(pPopulation)
{
	return;
}

ISelector::~ISelector()
{
	return;
}

void ISelector::DoEntry(void)
{
	wxLogDebug("TRACE: ISelector::DoEntry called");
}

void ISelector::DoExit(void)
{
	wxLogDebug("TRACE: ISelector::DoExit called");
}