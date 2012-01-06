#include "MainFrame.h"
#include "RectangleDrawer.h"

#include <ctime>

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_BUTTON(wxID_OK,     MainFrame::OnButtonTestClick)
	EVT_MENU(Minimal_About, MainFrame::OnAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 800))
, m_pRectangleDraw(NULL)
, m_pMainController(NULL)
{
    // set the frame icon
    SetIcon(wxICON(sample));

#if wxUSE_MENUS
    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
	helpMenu->Append(Minimal_About, _T("&About...\tF1"), _T("Show about dialog"));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, _T("&File"));
    menuBar->Append(helpMenu, _T("&Help"));

    // and attach this menu bar to the frame
    SetMenuBar(menuBar);
#endif // wxUSE_MENUS

#if wxUSE_STATUSBAR
    // create a status bar just for fun (by default with 1 pane only)
    CreateStatusBar(2);
    SetStatusText(_T("Welcome to Cutting proGRAM!"));
#endif // wxUSE_STATUSBAR

	m_pRectangleDraw = RectangleDrawer::CreateDrawer(this, 600, 600);
	m_pMainController = new MainController(m_pRectangleDraw);
    wxSizer* vsizer = new wxBoxSizer(wxVERTICAL);
    vsizer->Add(m_pRectangleDraw, 1, wxEXPAND);
    //vsizer->Add(m_pBtnTest, 0, wxALIGN_RIGHT);
    this->SetSizer(vsizer);
}

MainFrame::~MainFrame()
{
	delete m_pMainController;
    RectangleDrawer::DeleteDrawer();
}

void MainFrame::OnButtonTestClick(wxCommandEvent& WXUNUSED(event))
{
}

void MainFrame::OnAbout( wxCommandEvent& WXUNUSED(event) )
{
	wxLogDebug("MainFrame::OnAbout called");
	m_pMainController->Run();
}
