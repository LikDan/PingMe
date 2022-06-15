#include "MainPage.h"
#include "MainPage.g.cpp"
#include "pch.h"

#include "Monitor.h"
#include "Utils.h"

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
		ReadMonitors();
	}

	Windows::Foundation::IAsyncAction MainPage::ReadMonitors()
	{
		co_await readMonitors();
		for each (auto _monitor in monitors)
		{
			auto control = MonitorPreviewControl(_monitor.second);
			control.Margin({ 10, 10, 10, 10 });
			statusPanel().Children().InsertAt(0, control);

			_monitor.second.Parent(control);
		}
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

		monitors[monitor.Name()] = monitor;

		statusPanel().Children().InsertAt(0, control);

		saveMonitors();
	}

	Windows::Foundation::IAsyncAction MainPage::EventHandler(const IInspectable&, const RoutedEventArgs&)
	{
		SettingsDialog addMonitorDialog;

		addMonitorDialog.Title(winrt::box_value(L"Add new monitor"));
		addMonitorDialog.PrimaryButtonText(L"Ok");
		addMonitorDialog.CloseButtonText(L"Close");
		auto result = co_await addMonitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;

		for each (auto monitor in monitors)
		{
			monitor.second.Parent().Update();
		}
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
