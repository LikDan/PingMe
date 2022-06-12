#include "MainPage.h"
#include "MainPage.g.cpp"
#include "pch.h"

#include "AddMonitorDialog.h"
#include "Monitor.h"

#include "ctime";
#include "Monitors.h"

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
		auto dialogContent = PingMe::AddMonitorDialog();

		Controls::ContentDialog addMonitorDialog;

		addMonitorDialog.Title(winrt::box_value(L"Add new monitor"));
		addMonitorDialog.Content(dialogContent);
		addMonitorDialog.PrimaryButtonText(L"Ok");
		addMonitorDialog.CloseButtonText(L"Close");

		auto result = co_await addMonitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;

		dialogContent = addMonitorDialog.Content().as<PingMe::AddMonitorDialog>();
		auto monitor = dialogContent.Add();

		if (monitor == nullptr) co_return;

		auto control = MonitorPreviewControl(monitor);
		control.Margin({10, 10, 10, 10});

		monitors[monitor.Name()] = pair(monitor, control);

		statusPanel().Children().InsertAt(0, control);
	}

	void MainPage::EventHandler(const IInspectable&, const RoutedEventArgs&)
	{
		// monitors[L"Google"].event();
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
