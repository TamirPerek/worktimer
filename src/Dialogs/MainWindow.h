#pragma once

#include "Views/MainWindowView.h"

#include "../StateMachine.h"

#include <signals.h>

#include <string>
#include <memory>
#include <map>
#include <wx/preferences.h>

namespace Dialogs
{
	class DetailList;

	class MainWindow : public Views::MainWindow, public vdk::context
	{
	private:
		StateMachine m_StateMachine;
		std::string m_StatusText;

		DetailList *m_DetailListDialog = nullptr;
		wxPreferencesEditor *tPreferenceDialog = nullptr;

		std::map<std::string, int> m_DataForComboBox;

		void OnStart(wxCommandEvent &event) final;
		void OnStop(wxCommandEvent &event) final;
		void OnDumpToCSV(wxCommandEvent &event) final;
		void OnShowDetailList(wxCommandEvent &event) final;
		void OnShowOptions(wxCommandEvent &event) final;
		void OnAbout(wxCommandEvent &event) final;

		void MySetStatusText() noexcept;

		void InitCategoriesComboBox() noexcept;
		void SetStatusTextCallback(const std::string &) noexcept;
		void SetReusedDataFromListView(const std::string &xCategory, const std::string &xText) noexcept;

		static int DatabaseCallback(void *xListView, int xCount, char **xData, char **xColumns);


	public:
		MainWindow();
		explicit MainWindow(wxWindow *parent);
		~MainWindow();
	};

} // namespace Dialogs
