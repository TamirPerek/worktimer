#pragma once

#include "Views/DetailListView.h"

namespace Dialogs
{
    class DetailList : public Views::DetailList
    {
    private:
        /* data */
    public:
        DetailList();
        explicit DetailList(wxWindow *parent);
        ~DetailList();
    };
} // namespace Dialogs
