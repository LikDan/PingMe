#include "pch.h"
#include "AddMonitorDialog.h"
#if __has_include("AddMonitorDialog.g.cpp")
#include "AddMonitorDialog.g.cpp"
#endif

#include "Monitor.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Controls;

namespace winrt::PingMe::implementation
{
    AddMonitorDialog::AddMonitorDialog()
    {
        InitializeComponent();
    }


    hstring AddMonitorDialog::Add() {
        auto name = winrt::to_string(nameText().Text());
        auto host = winrt::to_string(hostText().Text());
        auto interval = winrt::to_string(intervalText().Text());

        monitors.insert(pair<winrt::hstring, Monitor>(hostText().Text(), { name, host, interval, {50, 255, 20}}));

        return hostText().Text();
    }
}
