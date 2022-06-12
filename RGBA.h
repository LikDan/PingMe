#pragma once

#include <winrt/Windows.UI.Xaml.Media.h>

#include "RGBA.g.h"

namespace winrt::PingMe::implementation
{
    struct RGBA : RGBAT<RGBA>
    {
        RGBA(int r, int g, int b, int a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        };

        RGBA(int r, int g, int b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = 255;
        };

        Windows::UI::Color color()
        {
            return winrt::Windows::UI::ColorHelper::FromArgb(a, r, g, b);
        }

        Windows::UI::Xaml::Media::SolidColorBrush brush()
        {
            return winrt::Windows::UI::Xaml::Media::SolidColorBrush(color());
        }

    private:
        int r, g, b, a;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct RGBA : RGBAT<RGBA, implementation::RGBA>
    {
    };
}
