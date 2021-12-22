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
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/listctrl.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace Dialogs::Views
{
	///////////////////////////////////////////////////////////////////////////////
	/// Class PreferencesPanel_Category
	///////////////////////////////////////////////////////////////////////////////
	class PreferencesPanel_Category : public wxPanel
	{
		private:

		protected:
			wxTextCtrl* m_textCtrlCategory;
			wxButton* m_buttonAddCategory;
			wxListCtrl* m_listCtrlCategories;
			wxButton* m_buttonDeleteCategory;

			// Virtual event handlers, override them in your derived class
			virtual void OnAddCategoryClicked( wxCommandEvent& event ) = 0;
			virtual void OnDeleteCategoryClicked( wxCommandEvent& event ) = 0;


		public:

			PreferencesPanel_Category( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

			~PreferencesPanel_Category();

	};

} // namespace Dialogs::Views

