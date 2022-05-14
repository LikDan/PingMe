#pragma once

#include "AddMonitorDialog.g.h"

namespace winrt::PingMe::implementation
{
    struct AddMonitorDialog : AddMonitorDialogT<AddMonitorDialog>
    {
        AddMonitorDialog();

        hstring Add();
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct AddMonitorDialog : AddMonitorDialogT<AddMonitorDialog, implementation::AddMonitorDialog>
    {
    };
}
