#pragma once
#include <winrt/Windows.UI.Xaml.Media.h>
#include "StatusControl.g.h"

#include "Monitor.h"

#include "json.hpp"

using json = nlohmann::json;

namespace winrt::PingMe::implementation
{
    struct StatusControl : StatusControlT<StatusControl>
    {
        StatusControl() { DefaultStyleKey(winrt::box_value(L"PingMe.StatusControl")); }


        winrt::Windows::UI::Xaml::Media::SolidColorBrush Color() {
            return winrt::unbox_value<winrt::Windows::UI::Xaml::Media::SolidColorBrush>(GetValue(m_colorProperty));
        }

        void Color(winrt::Windows::UI::Xaml::Media::SolidColorBrush const& value) {
            SetValue(m_colorProperty, winrt::box_value(value));
        }

        winrt::hstring MonitorName() {
            return winrt::unbox_value<winrt::hstring>(GetValue(m_nameProperty));
        }

        void MonitorName(winrt::hstring const& value) {
            SetValue(m_nameProperty, winrt::box_value(value));

            Update();
        }

        winrt::hstring Host() {
            return winrt::unbox_value<winrt::hstring>(GetValue(m_hostProperty));
        }

        void Host(winrt::hstring const& value) {
            SetValue(m_hostProperty, winrt::box_value(value));
        }

        winrt::hstring Cooldown() {
            return winrt::unbox_value<winrt::hstring>(GetValue(m_cooldownProperty));
        }

        void Cooldown(winrt::hstring const& value) {
            SetValue(m_cooldownProperty, winrt::box_value(value));
        }

        winrt::hstring Points() {
            return winrt::unbox_value<winrt::hstring>(GetValue(m_pointsProperty));
        }

        void Points(winrt::hstring const& value) {
            SetValue(m_pointsProperty, winrt::box_value(value));
        }


        static Windows::UI::Xaml::DependencyProperty ColorProperty() { return m_colorProperty; }
        static Windows::UI::Xaml::DependencyProperty MonitorNameProperty() { return m_nameProperty; }
        static Windows::UI::Xaml::DependencyProperty HostProperty() { return m_hostProperty; }
        static Windows::UI::Xaml::DependencyProperty CooldownProperty() { return m_cooldownProperty; }
        static Windows::UI::Xaml::DependencyProperty PointsProperty() { return m_pointsProperty; }

        static void OnChanged(Windows::UI::Xaml::DependencyObject const&, Windows::UI::Xaml::DependencyPropertyChangedEventArgs const&);

        void ClickHandler(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& args);

        void OnApplyTemplate();

        void Update();

    private:
        static Windows::UI::Xaml::DependencyProperty m_colorProperty;
        static Windows::UI::Xaml::DependencyProperty m_nameProperty;
        static Windows::UI::Xaml::DependencyProperty m_hostProperty;
        static Windows::UI::Xaml::DependencyProperty m_cooldownProperty;
        static Windows::UI::Xaml::DependencyProperty m_pointsProperty;
    };
}
namespace winrt::PingMe::factory_implementation
{
    struct StatusControl : StatusControlT<StatusControl, implementation::StatusControl>
    {
    };
}