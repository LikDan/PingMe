#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include "Monitor.h"
#include "AddMonitorDialog.h"

#include "ctime";

using namespace std;

using namespace winrt;
using namespace Windows::UI::Xaml;


namespace winrt::PingMe::implementation
{
    //map<hstring, PingMe::StatusControl> views;
    MainPage::MainPage() {
        InitializeComponent();
    }

    Windows::Foundation::IAsyncAction MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&) {
        auto dialogContent = PingMe::AddMonitorDialog();

        Controls::ContentDialog addMonitorDialog;

        addMonitorDialog.Title(winrt::box_value(L"Add new monitor"));
        addMonitorDialog.Content(dialogContent);
        addMonitorDialog.PrimaryButtonText(L"Ok");
        addMonitorDialog.CloseButtonText(L"Close");

        auto result = co_await addMonitorDialog.ShowAsync();

        if (result != winrt::Windows::UI::Xaml::Controls::ContentDialogResult::Primary) co_return;

        dialogContent = addMonitorDialog.Content().as<PingMe::AddMonitorDialog>();
        auto name = dialogContent.Add();

        if (name == L"") co_return;

        auto control = PingMe::StatusControl();
        control.Margin({10, 10, 10, 10});
        control.Host(name);
        
         monitorViews[name] = control;

        statusPanel().Children().InsertAt(0, control);
    }

    void MainPage::EventHandler(IInspectable const&, RoutedEventArgs const&) {
        monitors[L"google"].event();

        /*
        views[L"google"].Host(L"google2");
        views[L"google"].Host(L"google");*/
    }
}
