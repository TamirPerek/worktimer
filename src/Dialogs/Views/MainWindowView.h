///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/cshelp.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/statusbr.h>
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/msgdlg.h>
#include <wx/combobox.h>

///////////////////////////////////////////////////////////////////////////

namespace Dialogs::Views
{
    ///////////////////////////////////////////////////////////////////////////////
    /// Class MainWindow
    ///////////////////////////////////////////////////////////////////////////////
    class MainWindow : public wxFrame
    {
    private:
    protected:
        wxStaticText *m_Label1;
        wxTextCtrl *m_WorkCategory;
        wxStaticLine *m_staticline1;
        wxButton *m_BtStart;
        wxButton *m_BtStop;
        wxStatusBar *m_StatusBar;
        wxMenuBar *m_menubar1;
        wxMenu *m_menu1;
        wxComboBox *m_ComboboxCategories;

        // Virtual event handlers, override them in your derived class
        virtual void OnStart(wxCommandEvent &event) { event.Skip(); }
        virtual void OnStop(wxCommandEvent &event) { event.Skip(); }
        virtual void OnDumpToCSV(wxCommandEvent &event) { event.Skip(); }
        virtual void OnShowDetailList(wxCommandEvent &event) { event.Skip(); }
        virtual void OnShowOptions(wxCommandEvent &event) { event.Skip(); }
        virtual void OnAbout(wxCommandEvent &event) { event.Skip(); }

    public:
        MainWindow();
        MainWindow(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("WorkTimer"), const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(250, 300), long style = wxDEFAULT_FRAME_STYLE, const wxString &name = wxT("MainWIndow"));
        bool Create(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("WorkTimer"), const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(250, 300), long style = wxDEFAULT_FRAME_STYLE, const wxString &name = wxT("MainWIndow"));

        ~MainWindow();
    };

} // namespace Dialogs::Views
