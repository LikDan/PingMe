#include "pch.h"
#include "Pinger.h"
#if __has_include("Pinger.g.cpp")
#include "Pinger.g.cpp"
#endif

#include "HTTPRequests.h"
#include <chrono>


#include "json.hpp"
using json = nlohmann::json;

using namespace winrt;
using namespace Windows::UI::Xaml;

using namespace std::chrono;

namespace winrt::PingMe::implementation
{
    Pinger::Pinger() = default;

    Pinger::Pinger(PingMe::Monitor monitor, Windows::Foundation::EventHandler<PingMe::CheckEvent> const& handler)
    {
        this->monitor = monitor;
        this->handler = handler;

        this->timer = DispatcherTimer();
        this->timer.Interval(std::chrono::seconds{ monitor.Timeout() });

        auto lambda = [=](IInspectable const&, IInspectable const&) { Check(); };


        this->timer.Tick(lambda);
    }

    void Pinger::Pause()
    {
        this->timer.Stop();
    }

    void Pinger::Continue()
    {
        this->timer.Start();
    }

    void Pinger::Check()
    { 
        try
        {
            http::Request request{ to_string(monitor.Host()) };

            http::HeaderFields headerFields;
            if (monitor.Headers() != L"")
            {
                auto headersJson = json::parse(monitor.Headers());
                for (json::iterator it = headersJson.begin(); it != headersJson.end(); ++it) {
                    headerFields.push_back(std::pair(it.key(), it.value()));
                }
            }

            if (monitor.Cookies() != L"")
            {
                std::string cookies;
                auto cookiesJson = json::parse(monitor.Cookies());
                for (json::iterator it = cookiesJson.begin(); it != cookiesJson.end(); ++it) {
                    if (it != cookiesJson.begin()) cookies += ";";
                    cookies += it.key();
                    cookies += "=";
                    cookies += it.value();
                }

                headerFields.push_back(std::pair("Cookie", cookies));
            }

            auto startTime = system_clock::now().time_since_epoch().count();
            const auto response = request.send(to_string(monitor.Method()), to_string(monitor.Body()), headerFields);
            int ping = (system_clock::now().time_since_epoch().count() - startTime) / 100000;

            auto body = to_hstring(std::string{ response.body.begin(), response.body.end() });
            hstring headers;
            for each (auto header in response.headerFields)
            {
                headers = headers + L"{" + to_hstring(header.first) + L": " + to_hstring(header.second) + L"}\n";
            }

            handler(nullptr, CheckEvent(ping, response.status.code, body, headers, time(nullptr)));
        }
        catch (const std::exception& e)
        {
            handler(nullptr, CheckEvent(0, 0, L"", L"", time(nullptr)));
        }
    }

    bool Pinger::IsLaunching()
    {
        return this->timer.IsEnabled();
    }
}
