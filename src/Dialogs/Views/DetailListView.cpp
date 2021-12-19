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

DetailListView::DetailListView( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	auto tMainSizer = new wxBoxSizer( wxVERTICAL );

	auto tPickerSizer = new wxBoxSizer( wxHORIZONTAL );

	m_DatePickerFrom = new  wxDatePickerCtrl(this, wxID_ANY);
	m_DatePickerTo = new  wxDatePickerCtrl(this, wxID_ANY);
	tPickerSizer->Add(m_DatePickerFrom, 0, wxALL, 2);
	tPickerSizer->Add(m_DatePickerTo, 0, wxALL, 2);

	tMainSizer->Add(tPickerSizer, 0, wxALL, 5);

	m_ListView = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SORT_ASCENDING );
	tMainSizer->Add( m_ListView, 1, wxEXPAND, 5 );


	this->SetSizer( tMainSizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect
	m_DatePickerFrom->Connect(wxEVT_DATE_CHANGED, wxCommandEventHandler(DetailListView::DatePickerFromEvent), NULL, this);
	m_DatePickerTo->Connect(wxEVT_DATE_CHANGED, wxCommandEventHandler(DetailListView::DatePickerToEvent), NULL, this);
}

DetailListView::~DetailListView()
{
}
