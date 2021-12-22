///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWindowView.h"

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

MainWindow::MainWindow()
{
}

MainWindow::MainWindow(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
    this->Create(parent, id, title, pos, size, style, name);
}

bool MainWindow::Create(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
    if (!wxFrame::Create(parent, id, title, pos, size, style, name))
    {
        return false;
    }

    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxBoxSizer *bSizer1;
    bSizer1 = new wxBoxSizer(wxVERTICAL);

    auto tLabelWorkCategory = new wxStaticText(this, wxID_ANY, wxT("Category:"), wxDefaultPosition, wxDefaultSize, 0);
    tLabelWorkCategory->Wrap(-1);
    bSizer1->Add(tLabelWorkCategory, 0, wxALL, 5);

    m_ComboboxCategories = new wxComboBox(this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN | wxCB_READONLY);
    m_ComboboxCategories->SetSelection(-1);
    bSizer1->Add(m_ComboboxCategories, 0, wxALL, 5);

    m_Label1 = new wxStaticText(this, wxID_ANY, wxT("Work Text:"), wxDefaultPosition, wxDefaultSize, 0);
    m_Label1->Wrap(-1);
    bSizer1->Add(m_Label1, 0, wxALL, 5);

    m_WorkCategory = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    m_WorkCategory->SetToolTip(wxT("Enter work category"));
    m_WorkCategory->SetHelpText(wxT("Daily"));

    bSizer1->Add(m_WorkCategory, 0, wxALL, 5);

    m_staticline1 = new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);
    bSizer1->Add(m_staticline1, 0, wxEXPAND | wxALL, 5);

    wxGridSizer *gSizer2;
    gSizer2 = new wxGridSizer(0, 2, 0, 0);

    m_BtStart = new wxButton(this, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0);
    gSizer2->Add(m_BtStart, 0, wxALL, 5);

    m_BtStop = new wxButton(this, wxID_ANY, wxT("Stop"), wxDefaultPosition, wxDefaultSize, 0);
    m_BtStop->Enable(false);

    gSizer2->Add(m_BtStop, 0, wxALL, 5);

    bSizer1->Add(gSizer2, 1, wxEXPAND, 5);

    this->SetSizer(bSizer1);
    this->Layout();
    m_StatusBar = this->CreateStatusBar(1, wxSTB_DEFAULT_STYLE, wxID_ANY);
    m_menubar1 = new wxMenuBar(0);
    m_menu1 = new wxMenu();
    m_menu1->Append(wxID_ABOUT);
    m_menu1->Append(wxID_PREFERENCES);
    wxMenuItem *m_menuItemDump;
    m_menuItemDump = new wxMenuItem(m_menu1, wxID_ANY, wxString(wxT("Dump to csv")), wxEmptyString, wxITEM_NORMAL);
    m_menu1->Append(m_menuItemDump);

    wxMenuItem *m_menuItemDetail;
    m_menuItemDetail = new wxMenuItem(m_menu1, wxID_ANY, wxString(wxT("Show List")), wxEmptyString, wxITEM_NORMAL);
    m_menu1->Append(m_menuItemDetail);

    m_menubar1->Append(m_menu1, wxT("Options"));

    this->SetMenuBar(m_menubar1);

    this->Centre(wxBOTH);

    // Connect Events
    m_BtStart->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStart), NULL, this);
    m_BtStop->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStop), NULL, this);
    m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnDumpToCSV), this, m_menuItemDump->GetId());
    m_menu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnShowDetailList), this, m_menuItemDetail->GetId());
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainWindow::OnShowOptions, this, wxID_PREFERENCES);

    return true;
}

MainWindow::~MainWindow()
{
    // Disconnect Events
    m_BtStart->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStart), NULL, this);
    m_BtStop->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainWindow::OnStop), NULL, this);
}
