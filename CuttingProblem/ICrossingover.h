#pragma once

#include "Threadable.h"

#include "wx/wx.h"

class ICrossingover : public Threadable
{
private:
	virtual void	DoEntry(void) = 0;
	virtual void	DoExit(void) = 0;
};