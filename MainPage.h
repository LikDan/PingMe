#pragma once

#include "pch.h"
#include "MainPage.g.h"

namespace winrt::PingMe::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        Windows::Foundation::IAsyncAction ReadMonitors();

        void AddLog(Windows::Foundation::IInspectable const& sender, PingMe::CheckEventControl const& control);

        Windows::Foundation::IAsyncAction AddHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        Windows::Foundation::IAsyncAction SettingsHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void InfoHandler(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
