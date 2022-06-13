#pragma once

#include "SettingsDialog.g.h"

namespace winrt::PingMe::implementation
{
    struct SettingsDialog : SettingsDialogT<SettingsDialog>
    {
        SettingsDialog();

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::Foundation::IInspectable const& args);
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct SettingsDialog : SettingsDialogT<SettingsDialog, implementation::SettingsDialog>
    {
    };
}
