#pragma once

#include "winrt/Windows.UI.Xaml.h"
#include "winrt/Windows.UI.Xaml.Markup.h"
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "winrt/Windows.UI.Xaml.Controls.Primitives.h"
#include "MonitorDialog.g.h"

namespace winrt::PingMe::implementation
{
    struct MonitorDialog : MonitorDialogT<MonitorDialog>
    {
        MonitorDialog();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct MonitorDialog : MonitorDialogT<MonitorDialog, implementation::MonitorDialog>
    {
    };
}
