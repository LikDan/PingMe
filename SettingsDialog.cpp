#include "pch.h"
#include "SettingsDialog.h"
#if __has_include("SettingsDialog.g.cpp")
#include "SettingsDialog.g.cpp"
#endif

#include "Utils.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    SettingsDialog::SettingsDialog()
    {
        InitializeComponent();
        this->PrimaryButtonClick({ this, &SettingsDialog::ClickHandler });
    }

    void SettingsDialog::ClickHandler(IInspectable const&, IInspectable const&)
    {
        int h = std::stoi(to_string(ChartHoursText().Text()));
        settings.ChartHours(h);
    }
}
