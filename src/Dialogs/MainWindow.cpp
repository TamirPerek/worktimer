
#include "MainWindow.h"

#include "../Command.h"
#include "../StaticData.h"
#include "DetailList.h"
#include "spdlog/fmt/fmt.h"

namespace Dialogs
{

	MainWindow::MainWindow()
	{
		this->Create(nullptr);
		SetStatusText(StaticData::pathToResource.string());
		// SetStatusText("Welcome to WorkTime!");
	}

	MainWindow::MainWindow(wxWindow *parent)
	{
		this->Create(parent);
		SetStatusText(StaticData::pathToResource.string());
		// SetStatusText("Welcome to WorkTime!");
	}

	MainWindow::~MainWindow() = default;

	void MainWindow::OnStart(wxCommandEvent &event)
	{
		const auto tCategory = m_WorkCategory->GetLineText(0);
		m_StateMachine.Apply(Command{CommandType::Start, tCategory.ToStdString()});
		m_BtStart->Disable();
		m_BtStop->Enable();
		MySetStatusText();
	}
	void MainWindow::OnStop(wxCommandEvent &event)
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

	void MainWindow::OnDumpToCSV(wxCommandEvent &event)
	{
		m_StateMachine.Apply(Command{CommandType::Dump});
		SetStatusText("Dumped database to csv.");
	}

	void MainWindow::OnShowDetailList(wxCommandEvent &event)
	{
		m_DetailListDialog = new DetailList(this);//std::make_unique<DetailList>(this);
		m_DetailListDialog->Show();
	}
}