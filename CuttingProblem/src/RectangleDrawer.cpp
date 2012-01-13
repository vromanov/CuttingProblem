#include "RectangleDrawer.h"

#include "Vector2F.h"
#include "RectangleF.h"
#include "RectangleDB.h"
#include "MainController.h"
#include "Chromosome.h"
#include "DB.h"
#include "Utils.h"
#include "ConfigReader.h"

#include "wx/graphics.h"

BEGIN_EVENT_TABLE(RectangleDrawer, wxPanel)
	//EVT_PAINT(RectangleDrawer::OnPaint)
END_EVENT_TABLE()

RectangleDrawer::RectangleDrawer( wxFrame* pParent, int width, int height )
: wxPanel(pParent, 0, 0, width, height)
, m_pRectangleDB(NULL)
, m_pController(NULL)
, m_bDoScreenShot(false)
, m_fTime(0)
, m_fFitnress(0)
{

}

RectangleDrawer::~RectangleDrawer()
{
	if (m_pRectangleDB)
		delete m_pRectangleDB;
}

wxBitmap RectangleDrawer::GetScreenShot(wxDC& dc)
{
	const size_t HEIGHT = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_HEIGHT");
	const size_t WIDTH = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_WIDTH");
	const size_t SCALING_COEFF = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SCALE");
	const size_t SHIFT = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT");

	wxSize screenSize(wxGetDisplaySize().x + SHIFT, wxGetDisplaySize().y + SHIFT);
	wxBitmap bitmap(WIDTH * SCALING_COEFF + SHIFT, HEIGHT * SCALING_COEFF + SHIFT);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, wxGetDisplaySize().x, 
		wxGetDisplaySize().y, &dc, 0, 0);
	memDC.SelectObject(wxNullBitmap);
	return bitmap;
}

void RectangleDrawer::Draw(MainController* pCtrl, float fTime)
{
	m_pController = pCtrl;
	m_fTime = fTime;
	m_fFitnress = pCtrl->GetBestChromosome()->FitnessValue();

	if (m_pRectangleDB)
		delete m_pRectangleDB;

	m_pRectangleDB = new RectangleDB(pCtrl->GetBestChromosome()->GetRectangleDB());
	m_bDoScreenShot = true;

	wxPaintEvent event;
	OnPaint(event);
}

void RectangleDrawer::DrawRectangle(wxDC& dc, const Vector2F& topLeft, const Vector2F& bottomRight)
{
	const size_t SCALING_COEFF = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SCALE");
	const size_t SHIFT = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT");

	dc.SetBrush(wxColor(80, 190, 235));
	dc.SetPen( wxPen( wxColor(80,150,235), 2 ) );
	dc.DrawRectangle(topLeft.X() * SCALING_COEFF + SHIFT, topLeft.Y() * SCALING_COEFF + SHIFT, (bottomRight.X() - topLeft.X()) * SCALING_COEFF, (bottomRight.Y() - topLeft.Y()) * SCALING_COEFF);
}

void RectangleDrawer::DrawTime(wxDC& dc, float fTime)
{
	dc.SetBrush(wxColor(80, 190, 235));
	dc.SetPen( wxPen( wxColor(80,150,235), 2 ) );
	char str[16];
	sprintf_s(str, "%6.3f", fTime);
	dc.DrawText(str, 5, 5);
}

void RectangleDrawer::DrawFitness(wxDC& dc, float fFitness)
{
	dc.SetBrush(wxColor(0, 10, 235));
	dc.SetPen( wxPen( wxColor(80,10,35), 4 ) );
	char str[16];
	sprintf_s(str, "%6.3f", fFitness);
	dc.DrawText(str, 5, 20);
}


void RectangleDrawer::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxClientDC dc(this);
	dc.Clear();
	if (!m_pRectangleDB)
		return;
	DrawTime(dc, m_fTime);
	DrawFitness(dc, m_fFitnress);

	for (size_t i = 0, i_end = m_pRectangleDB->Size(); i < i_end; ++i)
	{
		if ((*m_pRectangleDB)[i]->GetStatus() == ON_FIELD)
			DrawRectangle(dc, (*m_pRectangleDB)[i]->GetTopLeft(), (*m_pRectangleDB)[i]->GetBottomRight());
	}
	if (m_bDoScreenShot)
	{
		char str[128];
		wxDateTime now = wxDateTime::Now();
		sprintf_s(str, "screenshots/%sconf%drepeat%d.bmp", 
			now.Format("%H.%M.%S", wxDateTime::CEST).c_str(), 
			m_pController->GetCurrentTestConfig(),
			m_pController->GetCurrentTestRepeat());
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