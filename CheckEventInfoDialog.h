#pragma once

#include "CheckEventInfoDialog.g.h"

namespace winrt::PingMe::implementation
{
    struct CheckEventInfoDialog : CheckEventInfoDialogT<CheckEventInfoDialog>
    {
        CheckEventInfoDialog(hstring monitorName, PingMe::CheckEvent e);
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct CheckEventInfoDialog : CheckEventInfoDialogT<CheckEventInfoDialog, implementation::CheckEventInfoDialog>
    {
    };
}
