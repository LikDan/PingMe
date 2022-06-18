#pragma once

#include "MonitorPage.g.h"
#include <regex>

namespace winrt::PingMe::implementation
{
    using namespace Windows::UI::Xaml;
    using namespace Windows::UI::Xaml::Input;

    struct MonitorPage : MonitorPageT<MonitorPage>
    {
        MonitorPage();
        MonitorPage(PingMe::Monitor);

        PingMe::Monitor Result();

        void TextUpdate(IInspectable const& sender, KeyRoutedEventArgs const& args);

    private:
        const std::regex urlRegex = std::regex("http://[a-zA-Z0-9%\-./]+");
        const std::regex jsonMapRegex = std::regex("\\{\"[^\"]+\":\"[^\"]+\"(?:,\"[^\"]+\":\"[^\"]*\"){0,}\\}");
        const std::regex timeoutRegex = std::regex("[0-9]{1,5}");

        Windows::Foundation::Collections::IVector<PingMe::CheckEvent> events;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct MonitorPage : MonitorPageT<MonitorPage, implementation::MonitorPage>
    {
    };
}
