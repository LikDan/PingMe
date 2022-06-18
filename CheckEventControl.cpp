#include "pch.h"
#include "CheckEventControl.h"
#if __has_include("CheckEventControl.g.cpp")
#include "CheckEventControl.g.cpp"
#endif
#pragma warning(disable : 4996)
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    CheckEventControl::CheckEventControl(hstring monitorName, PingMe::CheckEvent e)
    {
        this->monitorName = monitorName;
        this->e = e;


        InitializeComponent();

        auto color = e.color().brush();

        statusText().Text(to_hstring(e.StatusCode()) + L"/" + to_hstring(e.Ping()));
        statusText().Foreground(color);
        statusRectangle().Fill(color);

        monitorText().Text(monitorName);

        long long time_ = e.Time();
        auto time = localtime(&time_);
        dateText().Text(to_hstring(time->tm_mon + 1) + L"/" + to_hstring(time->tm_mday) + L"/" + to_hstring(time->tm_year + 1900) + L" " + to_hstring(time->tm_hour) + L":" + to_hstring(time->tm_min) + L":" + to_hstring(time->tm_sec));
    }

    Windows::Foundation::IAsyncAction CheckEventControl::InfoHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e) {
        CheckEventInfoDialog checkEventInfoDialog = CheckEventInfoDialog(this->monitorName, this->e);

        checkEventInfoDialog.Title(winrt::box_value(L"Info"));
        checkEventInfoDialog.CloseButtonText(L"Close");
        co_await checkEventInfoDialog.ShowAsync();
    }
}
