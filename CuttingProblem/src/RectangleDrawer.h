#pragma once

#include "RectangleDB.h"

#include "wx/wx.h"

class Vector2F;
class MainController;

class RectangleDrawer : public wxPanel
{
public:
	void		Draw(MainController* pCtrl, float fTime);
	
	static RectangleDrawer*	CreateDrawer(wxFrame* pParent = NULL, int width = 100, int height = 100);
	static void				DeleteDrawer();

protected:
	RectangleDrawer(wxFrame* pParent, int width, int height );
	~RectangleDrawer();

private:
	void					OnPaint( wxPaintEvent& event );
	void					DoDraw(wxClientDC& dc, bool isInnerInclude = true);
	wxBitmap				GetScreenShot(wxDC& dc);
	
	void					DrawBox(wxDC& dc);
	void					DrawRectangle(wxDC& dc, RectangleF* pRectangle, bool isInner, bool isInclude);
	void					DrawStats(wxDC& dc);

	RectangleDB*			m_pRectangleDB;
	MainController*			m_pController;
	bool					m_bDoScreenShot;
	float					m_fTime;
	float					m_fFitnress;

	static RectangleDrawer*	s_pRectangleDrawer;

	DECLARE_EVENT_TABLE()
};