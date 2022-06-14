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

        if (monitor.Method() == L"GET") MethodText().SelectedIndex(0);
        if (monitor.Method() == L"POST") MethodText().SelectedIndex(1);
        if (monitor.Method() == L"PUT") MethodText().SelectedIndex(2);
        if (monitor.Method() == L"DELETE") MethodText().SelectedIndex(3);
       

        BodyText().Text(monitor.Body());
        HeadersText().Text(monitor.Headers());
        CookiesText().Text(monitor.Cookies());

        TimeoutText().Text(to_hstring(monitor.Timeout()));

        TextUpdate(nullptr, nullptr);
    }
    
    PingMe::Monitor MonitorPage::Result() {
        int timeout = std::stoi(to_string(TimeoutText().Text()));
        auto method = unbox_value<hstring>(MethodText().SelectedValue().as<Controls::ComboBoxItem>().Content());
        return Monitor(NameText().Text(), HostText().Text(), method, BodyText().Text(), HeadersText().Text(), CookiesText().Text(), timeout);
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
