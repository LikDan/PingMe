#pragma once
#include "ChartControl.g.h"

#include "Monitor.h"

namespace winrt::PingMe::implementation
{
    struct ChartControl : ChartControlT<ChartControl>
    {
        ChartControl() { DefaultStyleKey(winrt::box_value(L"PingMe.ChartControl")); }

        winrt::hstring PointsJson() {
            return winrt::unbox_value<winrt::hstring>(GetValue(m_pointsJsonProperty));
        }

        void PointsJson(winrt::hstring const& value) {
            SetValue(m_pointsJsonProperty, winrt::box_value(value));
        }


        static Windows::UI::Xaml::DependencyProperty PointsJsonProperty() { return m_pointsJsonProperty; }

        static void OnChanged(Windows::UI::Xaml::DependencyObject const&, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        void OnApplyTemplate();


    private:
        static Windows::UI::Xaml::DependencyProperty m_pointsJsonProperty;
    };
}
namespace winrt::PingMe::factory_implementation
{
    struct ChartControl : ChartControlT<ChartControl, implementation::ChartControl>
    {
    };
}