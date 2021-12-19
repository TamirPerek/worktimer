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

    private:
        struct Impl;
        std::unique_ptr<Impl> m;

        void refresh() noexcept;

        void DatePickerFromEvent(wxCommandEvent& event) final;
        void DatePickerToEvent(wxCommandEvent& event) final;
    };
} // namespace Dialogs
