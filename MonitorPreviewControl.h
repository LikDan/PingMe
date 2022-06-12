#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MonitorPreviewControl.g.h"

namespace winrt::PingMe::implementation
{
    struct MonitorPreviewControl : MonitorPreviewControlT<MonitorPreviewControl>
    {
        MonitorPreviewControl();
        MonitorPreviewControl(winrt::PingMe::Monitor const& monitor);

        void Update();

        Windows::Foundation::IAsyncAction EditHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);

        winrt::PingMe::Monitor Monitor() { return this->monitor; }

    private:
        winrt::PingMe::Monitor monitor;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct MonitorPreviewControl : MonitorPreviewControlT<MonitorPreviewControl, implementation::MonitorPreviewControl>
    {
    };
}
