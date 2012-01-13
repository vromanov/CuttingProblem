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
	wxBitmap				GetScreenShot(wxDC& dc);

	void					DrawTime(wxDC& dc, float fTime);
	void					DrawRectangle(wxDC& dc, const Vector2F& topLeft, const Vector2F& bottomRight);
	void					DrawFitness(wxDC& dc, float fFitness);

	RectangleDB*			m_pRectangleDB;
	MainController*			m_pController;
	bool					m_bDoScreenShot;
	float					m_fTime;
	float					m_fFitnress;

	static RectangleDrawer*	s_pRectangleDrawer;

	DECLARE_EVENT_TABLE()
};