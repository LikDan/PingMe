#include "pch.h"
#include "CheckEventControl.h"
#if __has_include("CheckEventControl.g.cpp")
#include "CheckEventControl.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    CheckEventControl::CheckEventControl(hstring monitorName, PingMe::CheckEvent e)
    {
        InitializeComponent();
    }

}
