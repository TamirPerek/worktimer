#pragma once

#include "Views/DetailListView.h"

#include <signals.h>

#include <memory>

namespace Dialogs
{
    class DetailList : public Views::DetailListView, public vdk::context
    {
    public:
        DetailList();
        explicit DetailList(wxWindow *parent);
        ~DetailList();

        vdk::signal<void(std::string, std::string)> &getReuseDataSignal() const noexcept;

    private:
        struct Impl;
        std::unique_ptr<Impl> m;

        void refresh() noexcept;

        void DatePickerFromEvent(wxDateEvent &event) final;
        void DatePickerToEvent(wxDateEvent &event) final;
        void OnButtonClickedReuseData(wxCommandEvent &event) final;
    };
} // namespace Dialogs
