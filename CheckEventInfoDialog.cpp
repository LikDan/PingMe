#include "pch.h"
#include "CheckEventInfoDialog.h"
#if __has_include("CheckEventInfoDialog.g.cpp")
#include "CheckEventInfoDialog.g.cpp"
#endif

#pragma warning(disable : 4996)

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    CheckEventInfoDialog::CheckEventInfoDialog(hstring monitorName, PingMe::CheckEvent e)
    {
        InitializeComponent();

        statusText().Text(to_hstring(e.StatusCode()) + L"/" + to_hstring(e.Ping()));
        statusText().Foreground(e.color().brush());

        monitorText().Text(monitorName);

        long long time_ = e.Time();
        auto time = localtime(&time_);
        dateText().Text(to_hstring(time->tm_mon + 1) + L"/" + to_hstring(time->tm_mday) + L"/" + to_hstring(time->tm_year + 1900) + L" " + to_hstring(time->tm_hour) + L":" + to_hstring(time->tm_min) + L":" + to_hstring(time->tm_sec));

        headersText().Text(e.Headers());
        bodyText().Text(e.Body());
    }
}
