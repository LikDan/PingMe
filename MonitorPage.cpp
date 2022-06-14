#include "pch.h"
#include "MonitorPage.h"
#if __has_include("MonitorPage.g.cpp")
#include "MonitorPage.g.cpp"
#endif

#include <regex>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Input;


namespace winrt::PingMe::implementation
{
    MonitorPage::MonitorPage()
    {
        InitializeComponent();
        this->IsPrimaryButtonEnabled(false);
    }

    MonitorPage::MonitorPage(PingMe::Monitor monitor) : MonitorPage()
    {
        NameText().Text(monitor.Name());
        HostText().Text(monitor.Host());
        TimeoutText().Text(to_hstring(monitor.Timeout()));

        TextUpdate(nullptr, nullptr);
    }
    
    PingMe::Monitor MonitorPage::Result() {
        int timeout = std::stoi(to_string(TimeoutText().Text()));
        return Monitor(NameText().Text(), HostText().Text(), MethodText().Text(), BodyText().Text(), HeadersText().Text(), CookiesText().Text(), timeout);
    }

    void MonitorPage::TextUpdate(IInspectable const& sender, KeyRoutedEventArgs const& args)
    {
        bool enable = NameText().Text() != L"" &&
            std::regex_match(to_string(HostText().Text()), urlRegex) &&
            (HeadersText().Text() == L"" || std::regex_match(to_string(HeadersText().Text()), jsonMapRegex)) &&
            (CookiesText().Text() == L"" || std::regex_match(to_string(CookiesText().Text()), jsonMapRegex)) &&
            std::regex_match(to_string(TimeoutText().Text()), timeoutRegex);
        this->IsPrimaryButtonEnabled(enable);
    }
}
