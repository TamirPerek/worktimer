#pragma once

#include "Views/MainWindowView.h"

#include "../StateMachine.h"

#include <string>
#include <memory>

namespace Dialogs
{
	class DetailList;

	class MainWindow : public Views::MainWindow
	{
		StateMachine m_StateMachine;
		std::string m_StatusText;

		DetailList *m_DetailListDialog;

		void OnStart(wxCommandEvent &event) final;
		void OnStop(wxCommandEvent &event) final;
		void OnDumpToCSV(wxCommandEvent &event) final;
		void OnShowDetailList(wxCommandEvent &event) final;

		void MySetStatusText() noexcept;

	public:
		MainWindow();
		explicit MainWindow(wxWindow *parent);
		~MainWindow();
	};

} // namespace Dialogs
