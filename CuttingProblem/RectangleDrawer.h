#pragma once

#include "RectangleDB.h"

#include "wx/wx.h"


class RectangleDrawer : public wxPanel
{
public:
	void		Draw( const RectangleDB& rectangleDB );
	
	static RectangleDrawer*	CreateDrawer(wxFrame* pParent = NULL, int width = 100, int height = 100);
	static void				DeleteDrawer();

protected:
	RectangleDrawer(wxFrame* pParent, int width, int height );
	~RectangleDrawer();

private:
	void					OnPaint( wxPaintEvent& event );
	wxBitmap				GetScreenShot(wxDC& dc);

	RectangleDB*			m_pRectangleDB;
	bool					m_bDoScreenShot;

	static RectangleDrawer*	s_pRectangleDrawer;

	DECLARE_EVENT_TABLE()
};