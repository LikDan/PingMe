#include "MainPage.h"
#include "MainPage.g.cpp"
#include "pch.h"

#include "Monitor.h"
#include "Monitors.h"

#include "ctime";

using namespace winrt::Windows::UI::Xaml::Controls;

using namespace std;

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
	}

	Windows::Foundation::IAsyncAction MainPage::ClickHandler(const IInspectable&, const RoutedEventArgs&)
	{
		MonitorPage monitorDialog;

		monitorDialog.Title(winrt::box_value(L"Add new monitor"));
		monitorDialog.PrimaryButtonText(L"Ok");
		monitorDialog.CloseButtonText(L"Close");

		auto result = co_await monitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;

	
		auto monitor = monitorDialog.Result();

		auto control = MonitorPreviewControl(monitor);
		control.Margin({10, 10, 10, 10});

		monitor.Parent(control);

		monitors[monitor.Name()] = pair(monitor, control);

		statusPanel().Children().InsertAt(0, control);
	}

	Windows::Foundation::IAsyncAction MainPage::EventHandler(const IInspectable&, const RoutedEventArgs&)
	{
		MonitorPage addMonitorDialog;

		addMonitorDialog.Title(winrt::box_value(L"Add new monitor"));
		addMonitorDialog.PrimaryButtonText(L"Ok");
		addMonitorDialog.CloseButtonText(L"Close");
		auto result = co_await addMonitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;
  	}

	void MainPage::StartHandler(const IInspectable&, const RoutedEventArgs&)
	{
		// monitors[L"Google"].launch();
	}

	void MainPage::WriteHandler(const IInspectable&, const RoutedEventArgs&)
	{
	}

	void MainPage::Handler(const IInspectable&, const IInspectable&)
	{
		// monitors[L"Google"].event();
		// monitorViews[L"Google"].MonitorName(L"Google");
	}
}
