#pragma once

#include "Views/PreferencesPanel_Category.h"

#include <wx/preferences.h>
#include <signals.h>

#include <map>

namespace Dialogs
{
	class PreferencesPanel_Category : public Views::PreferencesPanel_Category, public vdk::context
	{
	public:
		PreferencesPanel_Category();
		PreferencesPanel_Category(wxWindow *xParent);

	private:
		void OnAddCategoryClicked(wxCommandEvent &event) final;
		void OnDeleteCategoryClicked(wxCommandEvent &event) final;

		void InitListCtrl() const noexcept;
		void AddDataToListCrtl() noexcept(false);

		static int DatabaseCallback(void *xListView, int xCount, char **xData, char **xColumns);
	
		std::map<std::string, int> m_DataForListCtrl;
	};

	class PrefsPageGeneral : public wxStockPreferencesPage
	{
	public:
		PrefsPageGeneral() : wxStockPreferencesPage(Kind_General) {}
		wxWindow *CreateWindow(wxWindow *parent) final
		{
			return new PreferencesPanel_Category(parent);
		}
	};
}