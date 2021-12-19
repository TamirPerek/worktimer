#include "DetailList.h"

#include "../Database.h"
#include "../Exception.h"
#include <signals.h>

#include <utility>
#include <string>
#include <sstream>
#include <iomanip>
#include <time.h>

#include <wx/dateevt.h>

namespace Dialogs
{
    static constexpr time_t gTwoWeeks = 1209600;

    struct DetailList::Impl
    {
        void InitListView(wxListCtrl &xListView, wxDatePickerCtrl &xDatePickerFrom, wxDatePickerCtrl &xDatePickerTo) noexcept;
        static int DumpCallback(void *, int xCount, char **xData, char **xColumns);
        static std::string TimepointToString(const long &) noexcept;
        void fillListWithData(wxListCtrl &xListView, const time_t &xFrom, const time_t &xTo) noexcept(false);
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

    void DetailList::Impl::InitListView(wxListCtrl &xListView, wxDatePickerCtrl &xDatePickerFrom, wxDatePickerCtrl &xDatePickerTo) noexcept
    {
        try
        {
            xListView.AppendColumn("Details");
            xListView.AppendColumn("Start");
            xListView.AppendColumn("End");
            xListView.AppendColumn("Duration (min)");

            fillListWithData(xListView, xDatePickerFrom.GetValue().GetTicks(), xDatePickerTo.GetValue().GetTicks());
        }
        catch (...)
        {
            Exception::handle();
        }
    }

    int DetailList::Impl::DumpCallback(void *xListView, int xCount, char **xData, char **xColumns)
    {
        auto [tListView, tCount] = *static_cast<std::pair<wxListCtrl *, int> *>(xListView);

        wxListItem tItem;
        tItem.SetId(tCount);
        // tItem.SetText("Desc");
        tListView->InsertItem(tItem);

        for (int i = 0; i < xCount; i++)
        {
            if (std::string{xColumns[i]} == std::string{"desc"})
            {
                tListView->SetItem(tCount, 0, xData[i]);
            }
            else if (std::string{xColumns[i]} == std::string{"start"})
            {
                const auto tTimePoint = std::stol(xData[i]);
                tListView->SetItem(tCount, 1, TimepointToString(tTimePoint));
            }
            else if (std::string{xColumns[i]} == std::string{"end"})
            {
                const auto tTimePoint = std::stol(xData[i]);
                tListView->SetItem(tCount, 2, TimepointToString(tTimePoint));
            }
            else if (std::string{xColumns[i]} == std::string{"duration"})
            {
                tListView->SetItem(tCount, 3, std::to_string(std::stoi(xData[i]) / 60));
            }
        }
        tCount++;

        return EXIT_SUCCESS;
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
        std::pair<wxListCtrl *, int> tData{&xListView, 0};

        xListView.DeleteAllItems();

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

    void DetailList::DatePickerFromEvent(wxCommandEvent &event)
    {
        refresh();
    }

    void DetailList::DatePickerToEvent(wxCommandEvent &event)
    {
        refresh();
    }
}
