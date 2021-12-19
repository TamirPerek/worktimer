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
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/datectrl.h>
#include <wx/datetime.h>
#include <wx/dateevt.h>

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
			wxListCtrl* m_ListView;
			wxDatePickerCtrl * m_DatePickerFrom;
			wxDatePickerCtrl *m_DatePickerTo;

			virtual void DatePickerFromEvent(wxCommandEvent& event) { event.Skip(); }
			virtual void DatePickerToEvent(wxCommandEvent& event) { event.Skip(); }

		public:

			DetailListView( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Detail list"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 400,239 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

			~DetailListView();

	};

} // namespace Dialogs::Views

