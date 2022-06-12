#include "pch.h"
#include "MonitorPreviewControl.h"
#if __has_include("MonitorPreviewControl.g.cpp")
#include "MonitorPreviewControl.g.cpp"
#endif
#include <Monitors.h>

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
	MonitorPreviewControl::MonitorPreviewControl() { InitializeComponent(); }

	MonitorPreviewControl::MonitorPreviewControl(winrt::PingMe::Monitor const& monitor) : MonitorPreviewControl()
	{
		this->monitor = monitor;

		Update();
	}

	void MonitorPreviewControl::Update()
	{
		MainContainer().Background(RGBA(255, 165, 0).brush());

		NameTextBlock().Text(this->monitor.Name());
		HostTextBlock().Text(this->monitor.Host());
		TimeoutTextBlock().Text(to_hstring(this->monitor.Timeout()));

		PingChart().Update(this->monitor.Events());
	}

	Windows::Foundation::IAsyncAction MonitorPreviewControl::EditHandler(IInspectable const&, RoutedEventArgs const&)
	{
		auto dialogContent = PingMe::AddMonitorDialog();
		dialogContent.Edit(this->monitor);

		Controls::ContentDialog addMonitorDialog;

		addMonitorDialog.Title(winrt::box_value(L"Edit monitor"));
		addMonitorDialog.Content(dialogContent);
		addMonitorDialog.PrimaryButtonText(L"Ok");
		addMonitorDialog.CloseButtonText(L"Close");

		auto result = co_await addMonitorDialog.ShowAsync();

		if (result != winrt::Windows::UI::Xaml::Controls::ContentDialogResult::Primary) co_return;

		dialogContent = addMonitorDialog.Content().as<PingMe::AddMonitorDialog>();
		auto newMonitor = dialogContent.Add();

		if (newMonitor == nullptr) co_return;

		auto name = this->monitor.Name();
		auto newName = newMonitor.Name();

		monitors[name].first = newMonitor;

		if (newName != name)
		{
			auto nodeHandler = monitors.extract(name);
			nodeHandler.key() = newName;
			monitors.insert(std::move(nodeHandler));
		}

		this->monitor = newMonitor;
		Update();
	}
}
