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
	const size_t SHIFT_X = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_X");
	const size_t SHIFT_Y = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_Y");

	wxSize screenSize(wxGetDisplaySize().x, wxGetDisplaySize().y);
	wxBitmap bitmap(WIDTH * SCALING_COEFF + 2, HEIGHT * SCALING_COEFF + 2);
	wxMemoryDC memDC;
	memDC.SelectObject(bitmap);
	memDC.Blit(0, 0, wxGetDisplaySize().x, 
		wxGetDisplaySize().y, &dc, SHIFT_X, SHIFT_Y);
	memDC.SelectObject(wxNullBitmap);
	return bitmap;
}

void RectangleDrawer::Draw(MainController* pCtrl, float fTime)
{
	m_pController = pCtrl;
	m_fTime = fTime;
	m_fFitnress = pCtrl->GetBestChromosome()->FitnessValue();
	m_fFitnress = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_HEIGHT") - m_fFitnress;

	if (m_pRectangleDB)
		delete m_pRectangleDB;

	m_pRectangleDB = new RectangleDB(pCtrl->GetBestChromosome()->GetRectangleDB());
	m_bDoScreenShot = true;

	wxPaintEvent event;
	OnPaint(event);
}

void RectangleDrawer::DrawBox(wxDC& dc)
{
	const size_t SCALING_COEFF = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SCALE");
	const size_t SHIFT_X = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_X");
	const size_t SHIFT_Y = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_Y");

	const size_t HEIGHT = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_HEIGHT");
	const size_t WIDTH = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_WIDTH");

	dc.DrawLine(SHIFT_X, SHIFT_Y, WIDTH * SCALING_COEFF + SHIFT_X, SHIFT_Y);
	dc.DrawLine(WIDTH * SCALING_COEFF + SHIFT_X, SHIFT_Y, WIDTH * SCALING_COEFF + SHIFT_X, HEIGHT * SCALING_COEFF + SHIFT_Y);
	dc.DrawLine(WIDTH * SCALING_COEFF + SHIFT_X, HEIGHT * SCALING_COEFF + SHIFT_Y, SHIFT_X, HEIGHT * SCALING_COEFF + SHIFT_Y);
	dc.DrawLine(SHIFT_X, HEIGHT * SCALING_COEFF + SHIFT_Y, SHIFT_X, SHIFT_Y);
}


void RectangleDrawer::DrawRectangle(wxDC& dc, const Vector2F& topLeft, const Vector2F& bottomRight)
{
	const size_t SCALING_COEFF = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SCALE");
	const size_t SHIFT_X = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_X");
	const size_t SHIFT_Y = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_SHIFT_Y");

	//dc.SetBrush(wxColor(80, 190, 235));
	//dc.SetPen( wxPen( wxColor(80,150,235), 2 ) );
	dc.SetBrush(*wxCYAN_BRUSH); // green filling
	dc.SetPen( wxPen( wxColor(0, 0, 0), 1 ) ); // 1-pixels-thick red outline
	dc.DrawRectangle(topLeft.X() * SCALING_COEFF + SHIFT_X, topLeft.Y() * SCALING_COEFF + SHIFT_Y, (bottomRight.X() - topLeft.X()) * SCALING_COEFF, (bottomRight.Y() - topLeft.Y()) * SCALING_COEFF);
}

void RectangleDrawer::DrawStats(wxDC& dc)
{
	char str[32];
	sprintf_s(str, "Time = %6.3fs", m_fTime);
	dc.DrawText(str, 5, 10);

	sprintf_s(str, "Fitness = %4.1f", m_fFitnress);
	dc.DrawText(str, 5, 25);

	const size_t HEIGHT = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_HEIGHT");
	sprintf_s(str, "Height = %d", HEIGHT);
	dc.DrawText(str, 5, 40);

	const size_t WIDTH = ConfigReader::GetInstance()->GetFileConfigIntValue("CANVAS_WIDTH");
	sprintf_s(str, "Width = %d", WIDTH);
	dc.DrawText(str, 5, 55);
}


void RectangleDrawer::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
	wxClientDC dc(this);
	dc.Clear();
	if (!m_pRectangleDB)
		return;

	DrawBox(dc);
	DrawStats(dc);

	for (size_t i = 0, i_end = m_pRectangleDB->Size(); i < i_end; ++i)
	{
		if ((*m_pRectangleDB)[i]->GetStatus() == ON_FIELD)
			DrawRectangle(dc, (*m_pRectangleDB)[i]->GetTopLeft(), (*m_pRectangleDB)[i]->GetBottomRight());
	}
	if (m_bDoScreenShot)
	{
		size_t uiCurrentFile = m_pController->GetCurrentTestFile();
		const char* fileName = ConfigReader::GetInstance()->GetTestName(uiCurrentFile).c_str();
		char str[128];
		wxDateTime now = wxDateTime::Now();
		sprintf_s(str, "screenshots/time_%s_file_%s_conf_%d_repeat_%d_fit_%4.1f.bmp", 
			now.Format("%H.%M.%S", wxDateTime::CEST).c_str(), 
			fileName,
			m_pController->GetCurrentTestConfig()+1,
			m_pController->GetCurrentTestRepeat(),
			m_fFitnress);
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