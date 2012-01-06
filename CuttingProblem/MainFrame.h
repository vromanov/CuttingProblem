// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "MainController.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

// ----------------------------------------------------------------------------
// resources
// ----------------------------------------------------------------------------

// the application icon (under Windows and OS/2 it is in resources and even
// though we could still include the XPM here it would be unused)
#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "../sample.xpm"
#endif

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

// IDs for the controls and the menu commands
enum
{
    // menu items
    Minimal_Quit = wxID_EXIT,

    // it is important for the id corresponding to the "About" command to have
    // this standard value as otherwise it won't be handled properly under Mac
    // (where it is special and put into the "Apple" menu)
    Minimal_About = wxID_ABOUT
};

class RectangleDrawer;

// Define a new frame type: this is going to be our main frame
class MainFrame : public wxFrame
{
public:
    // ctor(s)
    MainFrame(const wxString& title);
    ~MainFrame();

    // event handlers (these functions should _not_ be virtual)
    void        OnQuit(wxCommandEvent& event);
    void        OnAbout(wxCommandEvent& event);
	void        OnButtonTestClick(wxCommandEvent &event);

private:
	RectangleDrawer*	m_pRectangleDraw;
	MainController*		m_pMainController;


    // any class wishing to process wxWidgets events must use this macro
    DECLARE_EVENT_TABLE()
};

#endif