#pragma once
#include <regex>

#include "AddMonitorDialog.g.h"

namespace winrt::PingMe::implementation
{
    struct AddMonitorDialog : AddMonitorDialogT<AddMonitorDialog>
    {
        AddMonitorDialog();

        PingMe::Monitor Add();
        void Edit(PingMe::Monitor);

        const std::regex urlRegex = std::regex("^(http:\/\/|https:\/\/)(www.)?[a-zA-Z0-9-]+.([a-z]+)?\/?[0-9a-zA-Z%/-]*$");
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct AddMonitorDialog : AddMonitorDialogT<AddMonitorDialog, implementation::AddMonitorDialog>
    {
    };
}
