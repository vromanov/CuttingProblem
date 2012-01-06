#ifndef _IAGREGATOR_H_
#define _IAGREGATOR_H_

#include "Threadable.h"

#include "wx/wx.h"

class IAgregator : public Threadable
{
private:
	virtual void	DoEntry(void) = 0;
	virtual void	DoExit(void) = 0;
};
#endif