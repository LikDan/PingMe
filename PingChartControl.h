#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "PingChartControl.g.h"


namespace winrt::PingMe::implementation
{
    struct PingChartControl : PingChartControlT<PingChartControl>
    {
        PingChartControl();

        void Update(Windows::Foundation::Collections::IVector<PingMe::CheckEvent> events);
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct PingChartControl : PingChartControlT<PingChartControl, implementation::PingChartControl>
    {
    };
}
