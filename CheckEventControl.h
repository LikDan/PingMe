#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "CheckEventControl.g.h"

namespace winrt::PingMe::implementation
{
    struct CheckEventControl : CheckEventControlT<CheckEventControl>
    {
        CheckEventControl(hstring monitorName, PingMe::CheckEvent e);

        Windows::Foundation::IAsyncAction InfoHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        PingMe::CheckEvent e = PingMe::CheckEvent(nullptr);
        hstring monitorName;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct CheckEventControl : CheckEventControlT<CheckEventControl, implementation::CheckEventControl>
    {
    };
}
