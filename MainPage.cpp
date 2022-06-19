#include "MainPage.h"
#include "MainPage.g.cpp"
#include "pch.h"

#include "Monitor.h"
#include "Utils.h"

#include "ctime"

#include <algorithm>

using namespace winrt::Windows::UI::Xaml::Controls;

using namespace std;

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
	MainPage::MainPage()
	{
		InitializeComponent();
		Files().ReadSettings();
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

		std::sort(sortedEvents.begin(), sortedEvents.end(), [](std::pair<hstring, CheckEvent> e1, std::pair<hstring, CheckEvent> e2) { return e1.second.Time() < e2.second.Time(); });

		for (int i = 0; i < 100; i++) {
			int index = sortedEvents.size() + i - 100;
			if (index < 0) continue;

			this->AddLog(nullptr, PingMe::CheckEventControl(sortedEvents[index].first, sortedEvents[index].second));
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
		SettingsDialog settingsDialog;

		settingsDialog.Title(winrt::box_value(L"Settings"));
		settingsDialog.PrimaryButtonText(L"Ok");
		settingsDialog.CloseButtonText(L"Close");
		auto result = co_await settingsDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;

		for each (auto monitor in monitors)
		{
			monitor.second.Parent().Update();
		}

		Files().SaveSettings();
  	}

	void MainPage::InfoHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
	{
		Windows::System::Launcher::LaunchUriAsync(Windows::Foundation::Uri(L"https://github.com/LikDan/PingMe"));
	}
}
