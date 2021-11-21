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
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/grid.h>
#include <wx/gdicmn.h>
#include <wx/gbsizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace Dialogs::Views
{
    ///////////////////////////////////////////////////////////////////////////////
    /// Class DetailList
    ///////////////////////////////////////////////////////////////////////////////
    class DetailList : public wxFrame
    {
    private:
    protected:
        wxGrid *m_grid1;

    public:
        DetailList(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("Detail list"), const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

        ~DetailList();
    };

} // namespace Dialogs::Views
