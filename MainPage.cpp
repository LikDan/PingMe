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
		co_await Files().ReadMonitors();
		for each (auto _monitor in monitors)
		{
			auto control = MonitorPreviewControl(_monitor.second);
			control.Margin({ 10, 10, 10, 10 });
			statusPanel().Children().InsertAt(0, control);

			_monitor.second.Parent(control);
		}
	}

	void MainPage::DeleteMonitor(PingMe::MonitorPreviewControl monitor) {
		for (int i = 0; i < statusPanel().Children().Size(); i++)
		{
			if (statusPanel().Children().GetAt(i) != monitor) continue;

			statusPanel().Children().RemoveAt(i);
			break;
		}
	}

	Windows::Foundation::IAsyncAction MainPage::AddHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
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

		Files().SaveMonitors();
	}

	Windows::Foundation::IAsyncAction MainPage::SettingsHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		SettingsDialog addMonitorDialog;

		addMonitorDialog.Title(winrt::box_value(L"Settings"));
		addMonitorDialog.PrimaryButtonText(L"Ok");
		addMonitorDialog.CloseButtonText(L"Close");
		auto result = co_await addMonitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;

		for each (auto monitor in monitors)
		{
			monitor.second.Parent().Update();
		}
  	}

	void MainPage::InfoHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		system("chrome https://github.com/LikDan/PingMe");
	}
}
