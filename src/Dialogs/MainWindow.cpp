
#include "MainWindow.h"

#include "../Command.h"
#include "../StaticData.h"
#include "../Dump.h"
#include "DetailList.h"
#include "spdlog/fmt/fmt.h"

#include <wx/filedlg.h>
#include <wx/aboutdlg.h>

namespace Dialogs
{

	MainWindow::MainWindow()
	{
		this->Create(nullptr);
		SetStatusText("Welcome to WorkTime!");
	}

	MainWindow::MainWindow(wxWindow *parent)
	{
		this->Create(parent);
		SetStatusText("Welcome to WorkTime!");
	}

	MainWindow::~MainWindow() = default;

	void MainWindow::OnStart(wxCommandEvent &)
	{
		const auto tCategory = m_WorkCategory->GetLineText(0);
		m_StateMachine.Apply(Command{CommandType::Start, tCategory.ToStdString()});
		m_BtStart->Disable();
		m_BtStop->Enable();
		MySetStatusText();
	}
	void MainWindow::OnStop(wxCommandEvent &)
	{
		m_StateMachine.Apply(Command{CommandType::Stop});
		m_BtStop->Disable();
		m_BtStart->Enable();
		MySetStatusText();
	}

	void MainWindow::MySetStatusText() noexcept
	{
		m_StatusText = fmt::format("{}: {}", m_StateMachine.GetStatus(), m_StateMachine.GetState()->GetCommand());

		std::cout << m_StatusText << std::endl;
		SetStatusText(m_StatusText.c_str());
	}

	void MainWindow::OnDumpToCSV(wxCommandEvent &)
	{
		wxFileDialog tDumpFileLocationDialog(this, "Save DumpFile", "", "WorkTimerDump", "CSV files (*.csv)|*.csv", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (tDumpFileLocationDialog.ShowModal() == wxID_CANCEL)
			return; 

		std::filesystem::path tOutputPath{static_cast<std::string>(tDumpFileLocationDialog.GetPath())};
		Dump::DumpDatabase(tOutputPath);

		SetStatusText("Dumped database to csv.");
	}

	void MainWindow::OnShowDetailList(wxCommandEvent &evet)
	{
		m_DetailListDialog = new DetailList(this);
		m_DetailListDialog->Show();
	}

	void MainWindow::OnAbout(wxCommandEvent &)
	{
		wxAboutDialogInfo aboutInfo;
		aboutInfo.SetName("WorkTimer");
		aboutInfo.SetVersion("0.0.1");
		aboutInfo.SetDescription(_("just a small program to log time done for projects."));
		aboutInfo.SetCopyright("(C) 2021");
		aboutInfo.AddDeveloper("Nils Brödner");
		wxAboutBox(aboutInfo, this);
	}
}