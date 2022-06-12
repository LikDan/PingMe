#include "pch.h"
#include "AddMonitorDialog.h"
#if __has_include("AddMonitorDialog.g.cpp")
#include "AddMonitorDialog.g.cpp"
#endif

#include "winrt/Windows.UI.Popups.h"

#include "Monitors.h"
#include <regex>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Controls;

namespace winrt::PingMe::implementation
{

    using namespace Windows::UI::Popups;

    AddMonitorDialog::AddMonitorDialog() {
        InitializeComponent();
    }

    void AddMonitorDialog::Edit(PingMe::Monitor monitor) {
        nameText().Text(monitor.Name());
        hostText().Text(monitor.Host());
        intervalText().Text(winrt::to_hstring(monitor.Timeout()));
    }

    PingMe::Monitor AddMonitorDialog::Add() {
        auto name = nameText().Text();
        auto host = hostText().Text();
        auto interval = intervalText().Text();

        if (name == L"" || !regex_match(to_string(host), urlRegex) || !regex_match(to_string(interval), std::regex("[0-9]{1,5}"))) {
            MessageDialog dialog(L"Wrong data");
            dialog.ShowAsync();

            return PingMe::Monitor(nullptr);
        }

        int i = std::stoi(to_string(interval));
        return Monitor(name, host, i, Windows::Foundation::Collections::IVector<PingMe::CheckEvent>());
    }
}
