#include "DetailList.h"

#include "../Database.h"
#include "../Exception.h"
#include "../StaticData.h"
#include <signals.h>

#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>
#include <filesystem>
#include <map>

#include <wx/dateevt.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>

namespace Dialogs
{
    static constexpr time_t gTwoWeeks = 1209600;
    struct DetailList::Impl
    {

        struct UsefulDatabaseData
        {
            std::string category;
            std::string text;
        };
        struct DatabaseCallbackData
        {
            wxListCtrl *listCtrl{nullptr};
            int count{0};
            std::map<int, UsefulDatabaseData> *listData{nullptr};
        };

        void InitListView(wxListCtrl &xListView, wxDatePickerCtrl &xDatePickerFrom, wxDatePickerCtrl &xDatePickerTo) noexcept;
        static int DumpCallback(void *, int xCount, char **xData, char **xColumns);
        static std::string TimepointToString(const long &) noexcept;
        void fillListWithData(wxListCtrl &xListView, const time_t &xFrom, const time_t &xTo) noexcept(false);

        vdk::signal<void(std::string, std::string)> reuseDataSignal;

        std::map<int, UsefulDatabaseData> listData{};
    };

    DetailList::DetailList()
        : Views::DetailListView{nullptr}
    {
        m = std::make_unique<Impl>();

        wxDateTime tTimeTo = wxDateTime::Now();
        tTimeTo.SetMinute(59).SetHour(23);
        m_DatePickerTo->SetValue(tTimeTo);
        wxDateTime tTimeFrom(wxDateTime::Now().GetTicks() - gTwoWeeks);
        tTimeFrom.SetMinute(0).SetHour(0);
        m_DatePickerFrom->SetValue(tTimeFrom);

        m->InitListView(*m_ListView, *m_DatePickerFrom, *m_DatePickerTo);
        Database::getDatabaseEvent().connect(this, &DetailList::refresh);
    }
    DetailList::DetailList(wxWindow *xParent)
        : Views::DetailListView{xParent}
    {
        m = std::make_unique<Impl>();

        wxDateTime tTimeTo = wxDateTime::Now();
        tTimeTo.SetMinute(59).SetHour(23);
        m_DatePickerTo->SetValue(tTimeTo);
        wxDateTime tTimeFrom(wxDateTime::Now().GetTicks() - gTwoWeeks);
        tTimeFrom.SetMinute(0).SetHour(0);
        m_DatePickerFrom->SetValue(tTimeFrom);

        m->InitListView(*m_ListView, *m_DatePickerFrom, *m_DatePickerTo);
        Database::getDatabaseEvent().connect(this, &DetailList::refresh);
    }
    DetailList::~DetailList() = default;

    vdk::signal<void(std::string, std::string)> &DetailList::getReuseDataSignal() const noexcept
    {
        return m->reuseDataSignal;
    }

    void DetailList::Impl::InitListView(wxListCtrl &xListView, wxDatePickerCtrl &xDatePickerFrom, wxDatePickerCtrl &xDatePickerTo) noexcept
    {
        try
        {
            xListView.AppendColumn("Category");
            xListView.AppendColumn("Details");
            xListView.AppendColumn("Start");
            xListView.AppendColumn("End");
            xListView.AppendColumn("Duration (min)");
            xListView.SetColumnWidth(0, 100);
            xListView.SetColumnWidth(1, 100);
            xListView.SetColumnWidth(2, 200);
            xListView.SetColumnWidth(3, 200);
            xListView.SetColumnWidth(4, 100);

            fillListWithData(xListView, xDatePickerFrom.GetValue().GetTicks(), xDatePickerTo.GetValue().GetTicks());
        }
        catch (...)
        {
            Exception::handle();
        }
    }

    int DetailList::Impl::DumpCallback(void *xListView, int xCount, char **xData, char **xColumns)
    {
		 try
		 {
			 if (!xListView || xCount <= 0 || !xData || !xColumns)
				 THROWUIERROR("One ore more mandatory parameters are not fullfiled.");

			 auto tDTO = static_cast<DatabaseCallbackData *>(xListView);

			 //wxListItem tItem;
			 //tItem.SetId(tDTO->count);
			 //tItem.SetText(xData[0]);
			 //tDTO->listCtrl->InsertItem(tItem);
			 //tDTO->listCtrl->InsertItem(tDTO->count, _("col1ItemText"));
			 std::string tCategory;
			 std::string tText;

			 for (int i = 0; i < xCount; i++)
			 {
				 const auto tColumnName{ std::string{xColumns[i]} };

				 wxListItem tItem;
				 tItem.SetMask(wxLIST_MASK_TEXT);				 
				 tItem.SetId(tDTO->count);

				 if (tColumnName == std::string("text"))
				 {
					 tCategory = xData[i];					 
					 tItem.SetColumn(0);
					 tItem.SetText(tCategory);

					 tDTO->listCtrl->InsertItem(tItem);
				 }
				 else if (tColumnName == std::string{ "desc" })
				 {
					 tText = xData[i];
					 tItem.SetColumn(1);
					 tItem.SetText(tText);

					 tDTO->listCtrl->InsertItem(tItem);
				 }
				 else if (tColumnName == std::string{ "start" })
				 {
					 const auto tTimePoint = TimepointToString(std::stol(xData[i]));
					 tItem.SetColumn(2);
					 tItem.SetText(tTimePoint);

					 tDTO->listCtrl->InsertItem(tItem);
					 //tDTO->listCtrl->SetItem(tDTO->count, 2, TimepointToString(tTimePoint));
				 }
				 else if (tColumnName == std::string{ "end" })
				 {
					 const auto tTimePoint = TimepointToString(std::stol(xData[i]));
					 tItem.SetColumn(3);
					 tItem.SetText(tTimePoint);

					 tDTO->listCtrl->InsertItem(tItem);
					 //tDTO->listCtrl->SetItem(tDTO->count, 3, TimepointToString(tTimePoint));
				 }
				 else if (tColumnName == std::string{ "duration" })
				 {
					 const auto tDuration = std::to_string(std::stoi(xData[i]) / 60);
					 tItem.SetColumn(4);
					 tItem.SetText(tDuration);

					 tDTO->listCtrl->InsertItem(tItem);
					 //tDTO->listCtrl->SetItem(tDTO->count, 4, std::to_string(std::stoi(xData[i]) / 60));
				 }
			 }
			 tDTO->listData->try_emplace(tDTO->count, UsefulDatabaseData{ tCategory, tText });
			 tDTO->count++;

			 return EXIT_SUCCESS;
		 }
		 catch (...)
		 {
			 Exception::handle();
			 return EXIT_FAILURE;
		 }
    }

    std::string DetailList::Impl::TimepointToString(const long &time_date_stamp) noexcept
    {
        std::time_t temp = time_date_stamp;
        std::tm *t = std::gmtime(&temp);
        std::stringstream ss; // or if you're going to print, just input directly into the output stream
        ss << std::put_time(t, "%Y-%m-%d %I:%M:%S %p");
        return ss.str();
    }

    void DetailList::Impl::fillListWithData(wxListCtrl &xListView, const time_t &xFrom, const time_t &xTo) noexcept(false)
    {
        DatabaseCallbackData tData{&xListView, 0, &listData};

        xListView.DeleteAllItems();
        listData.clear();

        if (!Database::read(&DetailList::Impl::DumpCallback, &tData, xFrom, xTo))
            THROWUIERROR("Can't read data from database. Details: {}", "none");
    }
    void DetailList::refresh() noexcept
    {
        try
        {
            m->fillListWithData(*m_ListView, m_DatePickerFrom->GetValue().GetTicks(), m_DatePickerTo->GetValue().GetTicks());
        }
        catch (...)
        {
            Exception::handle();
        }
    }

    void DetailList::DatePickerFromEvent([[maybe_unused]] wxDateEvent &event)
    {
        refresh();
    }

    void DetailList::DatePickerToEvent([[maybe_unused]] wxDateEvent &event)
    {
        refresh();
    }

    void DetailList::OnButtonClickedReuseData([[maybe_unused]] wxCommandEvent &event)
    {
        const auto tSelected = m_ListView->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);

        const auto tMapResult = m->listData.find(tSelected);
        if (tMapResult == m->listData.end())
            return;

        getReuseDataSignal().emit(tMapResult->second.category, tMapResult->second.text);
    }
}
