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

		std::vector<std::pair<hstring, CheckEvent>> sortedEvents;

		for each (auto _monitor in monitors)
		{
			auto control = MonitorPreviewControl(_monitor.second);
			control.Margin({ 10, 10, 10, 10 });
			statusPanel().Children().InsertAt(0, control);

			_monitor.second.Parent(control);
			_monitor.second.LogHandler({ this, &MainPage::AddLog });

			auto events = _monitor.second.Events();
			for (int i = 0; i < events.Size(); i++) sortedEvents.push_back(std::pair(_monitor.second.Name(), events.GetAt(i)));
		}

		//source: https://www.programiz.com/dsa/insertion-sort
		for (int step = 1; step < sortedEvents.size(); step++) {
			long key = sortedEvents[step].second.Time();
			int j = step - 1;
			while (key < sortedEvents[j].second.Time() && j >= 0) {
				sortedEvents[j + 1] = sortedEvents[j];
				--j;
			}
			sortedEvents[j + 1] = sortedEvents[step];
		}

		for (int i = 0; i < 100; i++) {
			if (sortedEvents.size() + i - 100 < 0) continue;
			this->AddLog(nullptr, PingMe::CheckEventControl(sortedEvents[sortedEvents.size() + i - 100].first, sortedEvents[sortedEvents.size() + i - 100].second));
		}
	}

	void MainPage::AddLog(Windows::Foundation::IInspectable const& sender, PingMe::CheckEventControl const& control) {
		logPanel().Children().InsertAt(0, control);
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
		monitor.LogHandler({ this, &MainPage::AddLog });

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
