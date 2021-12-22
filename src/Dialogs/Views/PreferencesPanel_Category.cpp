///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.0-4761b0c)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PreferencesPanel_Category.h"

// Using the construction of a static object to ensure that the help provider is set
// wx Manages the most recent HelpProvider passed to ::Set, but not the previous ones
// If ::Set gets called more than once, the previous one is returned and should be deleted
class wxFBContextSensitiveHelpSetter
{
public:
wxFBContextSensitiveHelpSetter()
{
wxSimpleHelpProvider* help = new wxSimpleHelpProvider();
wxHelpProvider* old = wxHelpProvider::Set( help );
if (old != 0){
delete old;
}
}
};

static wxFBContextSensitiveHelpSetter s_wxFBSetTheHelpProvider;
///////////////////////////////////////////////////////////////////////////
using namespace Dialogs::Views;

PreferencesPanel_Category::PreferencesPanel_Category( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* bSizerMain;
	bSizerMain = new wxBoxSizer( wxVERTICAL );

	wxStaticText* m_staticTextCreateCategory;
	m_staticTextCreateCategory = new wxStaticText( this, wxID_ANY, wxT("Create a Work Category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextCreateCategory->Wrap( -1 );
	bSizerMain->Add( m_staticTextCreateCategory, 0, wxALL, 5 );

	wxBoxSizer* bSizerTextAndButton;
	bSizerTextAndButton = new wxBoxSizer( wxHORIZONTAL );

	m_textCtrlCategory = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTextAndButton->Add( m_textCtrlCategory, 0, wxALL, 5 );

	m_buttonAddCategory = new wxButton( this, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerTextAndButton->Add( m_buttonAddCategory, 0, wxALL, 5 );


	bSizerMain->Add( bSizerTextAndButton, 0, wxALL, 5 );

	wxStaticLine* m_staticline;
	m_staticline = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizerMain->Add( m_staticline, 0, wxEXPAND | wxALL, 5 );

	wxStaticText* m_staticTextCategoryOverview;
	m_staticTextCategoryOverview = new wxStaticText( this, wxID_ANY, wxT("Category overview"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticTextCategoryOverview->Wrap( -1 );
	bSizerMain->Add( m_staticTextCategoryOverview, 0, wxALL, 5 );

	m_listCtrlCategories = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SORT_ASCENDING | wxLC_SINGLE_SEL);
	bSizerMain->Add( m_listCtrlCategories, 1, wxEXPAND, 5 );

	m_buttonDeleteCategory = new wxButton( this, wxID_ANY, wxT("Delete selected category"), wxDefaultPosition, wxDefaultSize, 0 );
	m_buttonDeleteCategory->SetToolTip( wxT("Also deletes all work items that belong to the deleted category.") );

	bSizerMain->Add( m_buttonDeleteCategory, 0, wxALL, 5 );


	this->SetSizer( bSizerMain );
	this->Layout();

	// Connect Events
	m_buttonAddCategory->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesPanel_Category::OnAddCategoryClicked ), NULL, this );
	m_buttonDeleteCategory->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesPanel_Category::OnDeleteCategoryClicked ), NULL, this );
}

PreferencesPanel_Category::~PreferencesPanel_Category()
{
	// Disconnect Events
	m_buttonAddCategory->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesPanel_Category::OnAddCategoryClicked ), NULL, this );
	m_buttonDeleteCategory->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( PreferencesPanel_Category::OnDeleteCategoryClicked ), NULL, this );

}
