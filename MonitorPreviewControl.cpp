#include "pch.h"
#include "MonitorPreviewControl.h"
#if __has_include("MonitorPreviewControl.g.cpp")
#include "MonitorPreviewControl.g.cpp"
#endif
#include <Utils.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml::Media::Imaging;

namespace winrt::PingMe::implementation
{
	MonitorPreviewControl::MonitorPreviewControl() { InitializeComponent(); }

	MonitorPreviewControl::MonitorPreviewControl(PingMe::Monitor const& monitor) : MonitorPreviewControl()
	{
		this->monitor = monitor;

		Update();
	}

	void MonitorPreviewControl::Update()
	{
		if (this->monitor.Events().Size() < 1) MainContainer().Background(RGBA(255, 165, 0).brush());
		else MainContainer().Background(this->monitor.Events().GetAt(this->monitor.Events().Size() - 1).color().brush());


		NameTextBlock().Text(this->monitor.Name());
		HostTextBlock().Text(this->monitor.Host());
		TimeoutTextBlock().Text(to_hstring(this->monitor.Timeout()));

		PingChart().Update(this->monitor.Events());
		if (this->monitor.IsLaunching()) StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Pause.png")));
		else StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Play.png")));
		
	}

	void MonitorPreviewControl::StateChange(IInspectable const&, RoutedEventArgs const&)
	{
		if (this->monitor.IsLaunching())
		{
			this->monitor.Pause();
			StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Play.png")));
		}
		else
		{
			this->monitor.Continue();
			StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Pause.png")));
		}

		Files().SaveMonitors();
	}

	Windows::Foundation::IAsyncAction MonitorPreviewControl::EditHandler(IInspectable const&, RoutedEventArgs const&)
	{
		MonitorPage monitorDialog(this->monitor);

		monitorDialog.Title(winrt::box_value(L"Edit monitor"));
		monitorDialog.PrimaryButtonText(L"Ok");
		monitorDialog.CloseButtonText(L"Close");

		auto result = co_await monitorDialog.ShowAsync();

		if (result != Controls::ContentDialogResult::Primary) co_return;
		this->monitor.Pause();

		auto newMonitor = monitorDialog.Result();
		newMonitor.Parent(monitor.Parent());
		newMonitor.LogHandler(monitor.LogHandler());

		auto name = this->monitor.Name();
		auto newName = newMonitor.Name();

		monitors[name] = newMonitor;

		if (newName != name)
		{
			auto nodeHandler = monitors.extract(name);
			nodeHandler.key() = newName;
			monitors.insert(std::move(nodeHandler));
		}

		this->monitor = newMonitor;
		Files().SaveMonitors();

		StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Pause.png")));
		Update();
	}

	void MonitorPreviewControl::DeleteHandler(IInspectable const&, RoutedEventArgs const&)
	{
		this->monitor.Pause();
		monitors.erase(this->monitor.Name());
		monitorGrid().Visibility(Visibility::Collapsed);
		restoreGrid().Visibility(Visibility::Visible);

		Files().SaveMonitors();
	}

	void MonitorPreviewControl::CheckHandler(IInspectable const&, RoutedEventArgs const&)
	{
		this->monitor.Check();
	}

	void MonitorPreviewControl::RestoreHandler(IInspectable const&, RoutedEventArgs const&)
	{
		monitors[this->monitor.Name()] = this->monitor;
		this->monitor.Continue();

		restoreGrid().Visibility(Visibility::Collapsed);
		monitorGrid().Visibility(Visibility::Visible);

		StateImage().Source(BitmapImage(Uri(L"ms-appx:///Assets/Pause.png")));
		Files().SaveMonitors();
	}
}
