#include "DetailList.h"

namespace Dialogs
{
    DetailList::DetailList()
        : Views::DetailList{nullptr}
    {
    }
    DetailList::DetailList(wxWindow *xParent)
        : Views::DetailList{xParent}
    {
    }
    DetailList::~DetailList() = default;
}