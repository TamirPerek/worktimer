///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "DetailListView.h"

// Using the construction of a static object to ensure that the help provider is set
// wx Manages the most recent HelpProvider passed to ::Set, but not the previous ones
// If ::Set gets called more than once, the previous one is returned and should be deleted
class wxFBContextSensitiveHelpSetter
{
public:
    wxFBContextSensitiveHelpSetter()
    {
        wxSimpleHelpProvider *help = new wxSimpleHelpProvider();
        wxHelpProvider *old = wxHelpProvider::Set(help);
        if (old != 0)
        {
            delete old;
        }
    }
};

static wxFBContextSensitiveHelpSetter s_wxFBSetTheHelpProvider;
///////////////////////////////////////////////////////////////////////////
using namespace Dialogs::Views;

DetailList::DetailList(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxGridBagSizer *gbSizer2;
    gbSizer2 = new wxGridBagSizer(0, 0);
    gbSizer2->SetFlexibleDirection(wxBOTH);
    gbSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    m_grid1 = new wxGrid(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0);

    // Grid
    m_grid1->CreateGrid(5, 5);
    m_grid1->EnableEditing(true);
    m_grid1->EnableGridLines(true);
    m_grid1->EnableDragGridSize(false);
    m_grid1->SetMargins(0, 0);

    // Columns
    m_grid1->EnableDragColMove(false);
    m_grid1->EnableDragColSize(true);
    m_grid1->SetColLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

    // Rows
    m_grid1->EnableDragRowSize(true);
    m_grid1->SetRowLabelAlignment(wxALIGN_CENTER, wxALIGN_CENTER);

    // Label Appearance

    // Cell Defaults
    m_grid1->SetDefaultCellAlignment(wxALIGN_LEFT, wxALIGN_TOP);
    gbSizer2->Add(m_grid1, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALL, 5);

    this->SetSizer(gbSizer2);
    this->Layout();

    this->Centre(wxBOTH);
}

DetailList::~DetailList()
{
}
