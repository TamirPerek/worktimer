
#include "MainWindow.h"

#include "../Command.h"
#include "../StaticData.h"
#include "../Dump.h"
#include "../Database_Category.h"
#include "../Exception.h"
#include "DetailList.h"
#include "PreferencesPanel_Category.h"
#include "spdlog/fmt/fmt.h"

#include <wx/filedlg.h>
#include <wx/aboutdlg.h>

namespace Dialogs
{
	struct DatabaseCallbackData
	{
		wxComboBox *comboBox = nullptr;
		std::map<std::string, int> *dataToListCtrl = nullptr;
	};

	MainWindow::MainWindow()
	{
		Create(nullptr);
		SetStatusText("Welcome to WorkTime!");

		InitCategoriesComboBox();

		Database_Category::getDatabaseEvent().connect(this, &MainWindow::InitCategoriesComboBox);
		Exception::getExceptionSignal().connect(this, &MainWindow::SetStatusTextCallback);
	}

	MainWindow::MainWindow(wxWindow *parent)
	{
		this->Create(parent);
		SetStatusText("Welcome to WorkTime!");

		InitCategoriesComboBox();

		Database_Category::getDatabaseEvent().connect(this, &MainWindow::InitCategoriesComboBox);
		Exception::getExceptionSignal().connect(this, &MainWindow::SetStatusTextCallback);
	}

	MainWindow::~MainWindow() = default;

	void MainWindow::OnStart(wxCommandEvent &)
	{
		const auto tText = m_WorkCategory->GetLineText(0);
		int tCategoryID = 0;

		if (const auto tMapResult = m_DataForComboBox.find(m_ComboboxCategories->GetValue().ToStdString());
			tMapResult != m_DataForComboBox.end())
			tCategoryID = tMapResult->second;

		m_StateMachine.Apply(Command{CommandType::Start, tText.ToStdString(), tCategoryID});
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

	void MainWindow::OnShowDetailList(wxCommandEvent &)
	{
		m_DetailListDialog = new DetailList(this);
		m_DetailListDialog->getReuseDataSignal().connect(this, &MainWindow::SetReusedDataFromListView);

		m_DetailListDialog->Show();
	}

	void MainWindow::OnShowOptions(wxCommandEvent &)
	{
		if (!tPreferenceDialog)
		{
			tPreferenceDialog = new wxPreferencesEditor("Options");
			tPreferenceDialog->AddPage(new PrefsPageGeneral());
		}
		tPreferenceDialog->Show(this);
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

	void MainWindow::InitCategoriesComboBox() noexcept
	{
		try
		{
			DatabaseCallbackData tData{m_ComboboxCategories, &m_DataForComboBox};

			m_ComboboxCategories->Clear();
			m_DataForComboBox.clear();

			if (!Database_Category::read(&MainWindow::DatabaseCallback, &tData))
				THROWUIERROR("Can't read data from database. Details: {}", "none");

			if (m_ComboboxCategories->GetCount() > 0)
				m_ComboboxCategories->SetSelection(0);
		}
		catch (...)
		{
			Exception::handle();
		}
	}

	void MainWindow::SetStatusTextCallback(const std::string &xIn) noexcept
	{
		SetStatusText(xIn);
	}

	void MainWindow::SetReusedDataFromListView(const std::string &xCategory, const std::string &xText) noexcept
	{
		if (m_StateMachine.GetState()->Name() != State::Start{}.Name())
		{
			wxMessageBox("The reuse of data is only allowed if no time recording is active.");
			return;
		}

		m_WorkCategory->SetValue(xText);

		const auto tComboBoxResult = m_ComboboxCategories->FindString(xCategory);
		if (tComboBoxResult == wxNOT_FOUND)
			return;

		m_ComboboxCategories->Select(tComboBoxResult);
	}

	int MainWindow::DatabaseCallback(void *xListView, int xCount, char **xData, char **xColumns)
	{
		if (!xListView || xCount <= 0 || !xData || !xColumns)
			return EXIT_FAILURE;

		const auto tDataBaseData = static_cast<DatabaseCallbackData *>(xListView);

		tDataBaseData->comboBox->Append(xData[1]);

		tDataBaseData->dataToListCtrl->try_emplace(xData[1], std::stoi(std::string{xData[0]}));

		return EXIT_SUCCESS;
	}
}