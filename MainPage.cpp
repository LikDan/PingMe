#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include "Monitor.h"

#include "ctime";

using namespace std;

using namespace winrt;
using namespace Windows::UI::Xaml;


namespace winrt::PingMe::implementation
{
    map<hstring, StatusControl> views;
    MainPage::MainPage() {
        InitializeComponent();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&) {
        time_t t = time(0) - 60 * 60 * 12;
        monitors.insert(pair<winrt::hstring, Monitor>(L"google", { "Working", "google.com", "5min", {50, 255, 20}, { {100, t, 200},  {150, t + 60 * 30, 200},  {70, t + 60 * 90, 400},  {201, t + 60 * 120, 400},  {20, t + 60 * 200, 200} } }));

        auto control = StatusControl();
        control.Margin({ 10, 10, 10, 10 });
        control.Host(L"google");

        views[L"google"] = control;

        statusPanel().Children().InsertAt(0, control);
    }

    void MainPage::EventHandler(IInspectable const&, RoutedEventArgs const&) {
        monitors[L"google"].event();

        views[L"google"].Host(L"google2");
        views[L"google"].Host(L"google");
    }
}
