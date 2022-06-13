#pragma once

#include "Settings.g.h"

namespace winrt::PingMe::implementation
{
    struct Settings : SettingsT<Settings>
    {
        Settings() = default;

        void ChartHours(int chartHours) { this->chartHours = chartHours; };
        int ChartHours() { return this->chartHours; };

    private:
        int chartHours = 12;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
