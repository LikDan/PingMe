#include "pch.h"
#include "AddMonitorDialog.h"
#if __has_include("AddMonitorDialog.g.cpp")
#include "AddMonitorDialog.g.cpp"
#endif

#include "winrt/Windows.UI.Popups.h"

#include "Monitor.h"
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

    void AddMonitorDialog::Edit(hstring name) {
        auto monitor = monitors[name];

        nameText().Text(winrt::to_hstring(monitor.name));
        hostText().Text(winrt::to_hstring(monitor.host));
        intervalText().Text(winrt::to_hstring(monitor.cooldown));
    }

    hstring AddMonitorDialog::Add() {
        auto name = winrt::to_string(nameText().Text());
        auto host = winrt::to_string(hostText().Text());
        auto interval = winrt::to_string(intervalText().Text());

        if (name == "" || !regex_match(host, urlRegex) || !regex_match(interval, std::regex("[0-9]{1,2}"))) {
            MessageDialog dialog(L"Wrong data");
            dialog.ShowAsync();

            return L"";
        }

        monitors.insert(pair<winrt::hstring, Monitor>(hostText().Text(), { name, host, interval, {50, 255, 20}}));

        return hostText().Text();
    }
}
