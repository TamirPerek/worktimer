#include "PreferencesPanel_Category.h"

#include "../Database_Category.h"
#include "../Exception.h"

#include <wx/msgdlg.h>

namespace Dialogs
{
    struct DatabaseCallbackData
    {
        wxListCtrl *listCtrl = nullptr;
        int count{0};
        std::map<std::string, int> *dataToListCtrl = nullptr;
    };

    PreferencesPanel_Category::PreferencesPanel_Category()
        : Views::PreferencesPanel_Category{nullptr}
    {
        try
        {
            InitListCtrl();
            AddDataToListCrtl();

            Database_Category::getDatabaseEvent().connect(this, &PreferencesPanel_Category::AddDataToListCrtl);
        }
        catch (...)
        {
            Exception::handle();
        }
    }
    PreferencesPanel_Category::PreferencesPanel_Category(wxWindow *xParent)
        : Views::PreferencesPanel_Category{xParent}
    {
        try
        {
            InitListCtrl();
            AddDataToListCrtl();

            Database_Category::getDatabaseEvent().connect(this, &PreferencesPanel_Category::AddDataToListCrtl);
        }
        catch (...)
        {
            Exception::handle();
        }
    }
	 void PreferencesPanel_Category::InitListCtrl() const noexcept
    {
        m_listCtrlCategories->AppendColumn("Description");
        m_listCtrlCategories->SetColumnWidth(0, 200);
    }
    void PreferencesPanel_Category::AddDataToListCrtl() noexcept(false)
    {
        DatabaseCallbackData tData{m_listCtrlCategories, 0, &m_DataForListCtrl};
        m_listCtrlCategories->DeleteAllItems();
        m_DataForListCtrl.clear();

        if (!Database_Category::read(&PreferencesPanel_Category::DatabaseCallback, &tData))
            THROWUIERROR("Can't read data from database. Details: {}", "none");
    }
    int PreferencesPanel_Category::DatabaseCallback(void *xListView, int xCount, char **xData, char **xColumns)
    {
        if (!xListView || xCount <= 0 || !xData || !xColumns)
            return EXIT_FAILURE;

        const auto tDataBaseData = static_cast<DatabaseCallbackData *>(xListView);

        wxListItem tItem;
        tItem.SetId(tDataBaseData->count);
        tItem.SetText(xData[1]);
        tDataBaseData->listCtrl->InsertItem(tItem);
        tDataBaseData->count++;

        tDataBaseData->dataToListCtrl->try_emplace(xData[1], std::stoi(std::string{xData[0]}));

        return EXIT_SUCCESS;
    }

    void PreferencesPanel_Category::OnAddCategoryClicked([[maybe_unused]] wxCommandEvent &event)
    {
        try
        {
            const auto tCategory = m_textCtrlCategory->GetLineText(0).ToStdString();
            Database_Category_DTO tDTO{0, tCategory};

            if (Database_Category::insert(tDTO) <= 0)
                THROWUIERROR("Can't insert data to database. Details: {}", tDTO.text);
        }
        catch (...)
        {
            Exception::handle();
        }
    }
    void PreferencesPanel_Category::OnDeleteCategoryClicked([[maybe_unused]] wxCommandEvent &event)
    {
        try
        {
            const auto tSelectedItem = m_listCtrlCategories->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

            if (tSelectedItem == wxNOT_FOUND)
                return;

            const auto tMapResult = m_DataForListCtrl.find(m_listCtrlCategories->GetItemText(tSelectedItem).ToStdString());
            if (tMapResult == m_DataForListCtrl.end())
                return;

            if (wxMessageBox("Are you sure you want to delete the category?\nAll work entries belonging to the category are also deleted.", "Confirm", wxYES_NO, this) == wxNO)
                return;

            Database_Category_DTO tDTO{tMapResult->second, tMapResult->first};

            if (!Database_Category::remove(tDTO))
                THROWUIERROR("Can't delete data from database. ID: <{}>", tDTO.id);
        }
        catch (...)
        {
            Exception::handle();
        }
    }
}