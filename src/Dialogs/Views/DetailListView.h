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
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/sizer.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

namespace Dialogs::Views
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class DetailListView
	///////////////////////////////////////////////////////////////////////////////
	class DetailListView : public wxFrame
	{
	private:
	protected:
		wxDatePickerCtrl *m_DatePickerFrom;
		wxDatePickerCtrl *m_DatePickerTo;
		wxListCtrl *m_ListView;
		wxButton *m_buttonReuseData;

		// Virtual event handlers, override them in your derived class
		virtual void DatePickerFromEvent(wxDateEvent &event) = 0;
		virtual void DatePickerToEvent(wxDateEvent &event) = 0;
		virtual void OnButtonClickedReuseData(wxCommandEvent &event) = 0;

	public:
		DetailListView(wxWindow *parent, wxWindowID id = wxID_ANY, const wxString &title = wxT("Detail list"), const wxPoint &pos = wxDefaultPosition, const wxSize &size = wxSize(700, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

		~DetailListView();
	};

} // namespace Dialogs::Views
