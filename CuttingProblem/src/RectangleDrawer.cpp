#include "RectangleDrawer.h"

#include "Vector2F.h"
#include "RectangleF.h"
#include "RectangleDB.h"
#include "DB.h"

#include "wx/graphics.h"

BEGIN_EVENT_TABLE(RectangleDrawer, wxPanel)
	//EVT_PAINT(RectangleDrawer::OnPaint)
END_EVENT_TABLE()

RectangleDrawer::RectangleDrawer( wxFrame* pParent, int width, int height )
: wxPanel(pParent, 0, 0, width, height)
, m_pRectangleDB(NULL)
, m_bDoScreenShot(false)
, m_fTime(0)
{

}

RectangleDrawer::~RectangleDrawer()
{
	if (m_pRectangleDB)
		delete m_pRectangleDB;
}

wxBitmap RectangleDrawer::GetScreenShot(wxDC& dc)
{
	wxSize screenSize(600, 600);
	wxBitmap bitmap(screenSize.x, screenSize.y);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, wxGetDisplaySize().x, 
		wxGetDisplaySize().y + 100, & dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);
	return bitmap;
}

void RectangleDrawer::Draw( const RectangleDB& rectangleDB, float time )
{
	m_fTime = time;

	if (m_pRectangleDB)
		delete m_pRectangleDB;

	m_pRectangleDB = new RectangleDB(rectangleDB);
	m_bDoScreenShot = true;

	wxPaintEvent event;
	OnPaint(event);
}

void RectangleDrawer::DrawRectangle(wxDC& dc, const Vector2F& topLeft, const Vector2F& bottomRight)
{
	const size_t SCALING_COEFF = 10;
	const size_t SHIFT = 50;

	dc.SetBrush(wxColor(80, 190, 235));
	dc.SetPen( wxPen( wxColor(80,150,235), 2 ) );
	dc.DrawRoundedRectangle(topLeft.X() * SCALING_COEFF + SHIFT, topLeft.Y() * SCALING_COEFF + SHIFT, (bottomRight.X() - topLeft.X()) * SCALING_COEFF, (bottomRight.Y() - topLeft.Y()) * SCALING_COEFF, 2);
}

void RectangleDrawer::DrawTime(wxDC& dc, float fTime)
{
	dc.SetBrush(wxColor(80, 190, 235));
	dc.SetPen( wxPen( wxColor(80,150,235), 2 ) );
	char str[16];
	sprintf_s(str, "%f", fTime);
	dc.DrawText(str, 5, 5);
}

void RectangleDrawer::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxClientDC dc(this);
	dc.Clear();
	if (!m_pRectangleDB)
		return;
	DrawTime(dc, m_fTime);

	for (size_t i = 0, i_end = m_pRectangleDB->Size(); i < i_end; ++i)
	{
		if ((*m_pRectangleDB)[i]->GetStatus() == ON_FIELD)
			DrawRectangle(dc, (*m_pRectangleDB)[i]->GetTopLeft(), (*m_pRectangleDB)[i]->GetBottomRight());
	}
	if (m_bDoScreenShot)
	{
		char str[32];
		wxDateTime now = wxDateTime::Now();
		sprintf_s(str, "screenshots/%s.bmp", now.Format("%H.%M.%S", wxDateTime::CEST).c_str());
		GetScreenShot(dc).SaveFile(str, wxBITMAP_TYPE_BMP);
		m_bDoScreenShot = false;
	}
}

RectangleDrawer* RectangleDrawer::CreateDrawer(wxFrame* pParent, int width, int height)
{
	if (!s_pRectangleDrawer)
		s_pRectangleDrawer = new RectangleDrawer(pParent, width, height);
	return s_pRectangleDrawer;
}

void RectangleDrawer::DeleteDrawer()
{
	if (s_pRectangleDrawer)
	{
		delete s_pRectangleDrawer;
		s_pRectangleDrawer = NULL;
	}
}

RectangleDrawer* RectangleDrawer::s_pRectangleDrawer = NULL;