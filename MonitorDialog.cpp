#include "pch.h"
#include "MonitorDialog.h"
#if __has_include("MonitorDialog.g.cpp")
#include "MonitorDialog.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    MonitorDialog::MonitorDialog()
    {
        InitializeComponent();
    }

    int32_t MonitorDialog::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MonitorDialog::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MonitorDialog::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        Button().Content(box_value(L"Clicked"));
    }
}
