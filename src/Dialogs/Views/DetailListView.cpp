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

DetailListView::DetailListView(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &pos, const wxSize &size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer *tMainSizer;
	tMainSizer = new wxBoxSizer(wxVERTICAL);

	wxPanel *tMainPanel;
	tMainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	wxBoxSizer *tPanelSizer;
	tPanelSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer *tPickerSizer;
	tPickerSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText *tStaticTextStart;
	tStaticTextStart = new wxStaticText(tMainPanel, wxID_ANY, wxT("Start:"), wxDefaultPosition, wxDefaultSize, 0);
	tStaticTextStart->Wrap(-1);
	tPickerSizer->Add(tStaticTextStart, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

	m_DatePickerFrom = new wxDatePickerCtrl(tMainPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	tPickerSizer->Add(m_DatePickerFrom, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

	wxStaticText *tStaticTextEnd;
	tStaticTextEnd = new wxStaticText(tMainPanel, wxID_ANY, wxT("End:"), wxDefaultPosition, wxDefaultSize, 0);
	tStaticTextEnd->Wrap(-1);
	tPickerSizer->Add(tStaticTextEnd, 0, wxALIGN_CENTER_VERTICAL | wxLEFT, 5);

	m_DatePickerTo = new wxDatePickerCtrl(tMainPanel, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
	tPickerSizer->Add(m_DatePickerTo, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

	tPanelSizer->Add(tPickerSizer, 0, wxALL, 5);

	m_ListView = new wxListCtrl(tMainPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL | wxLC_SORT_ASCENDING);
	tPanelSizer->Add(m_ListView, 1, wxEXPAND | wxALL, 5);

	m_buttonReuseData = new wxButton(tMainPanel, wxID_ANY, wxT("Reuse work item"), wxDefaultPosition, wxDefaultSize, 0);
	tPanelSizer->Add(m_buttonReuseData, 0, wxALL, 5);

	tMainPanel->SetSizer(tPanelSizer);
	tMainPanel->Layout();
	tPanelSizer->Fit(tMainPanel);
	tMainSizer->Add(tMainPanel, 1, wxEXPAND | wxALL, 0);

	this->SetSizer(tMainSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_DatePickerFrom->Connect(wxEVT_DATE_CHANGED, wxDateEventHandler(DetailListView::DatePickerFromEvent), NULL, this);
	m_DatePickerTo->Connect(wxEVT_DATE_CHANGED, wxDateEventHandler(DetailListView::DatePickerToEvent), NULL, this);
	m_buttonReuseData->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailListView::OnButtonClickedReuseData), NULL, this);
}

DetailListView::~DetailListView()
{
	// Disconnect Events
	m_DatePickerFrom->Disconnect(wxEVT_DATE_CHANGED, wxDateEventHandler(DetailListView::DatePickerFromEvent), NULL, this);
	m_DatePickerTo->Disconnect(wxEVT_DATE_CHANGED, wxDateEventHandler(DetailListView::DatePickerToEvent), NULL, this);
	m_buttonReuseData->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DetailListView::OnButtonClickedReuseData), NULL, this);
}
