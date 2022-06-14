#include "pch.h"
#include "Pinger.h"
#if __has_include("Pinger.g.cpp")
#include "Pinger.g.cpp"
#endif

#include "HTTPRequests.h"
#include <chrono>

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
        this->timer.Start();

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

            

            auto startTime = system_clock::now().time_since_epoch().count();
            const auto response = request.send(to_string(monitor.Method()), to_string(monitor.Body()), {});
            int ping = (system_clock::now().time_since_epoch().count() - startTime) / 100000;

            auto body = to_hstring(std::string{ response.body.begin(), response.body.end() });
            hstring headers;
            for each (auto header in response.headerFields)
            {
                headers = headers + L"{" + to_hstring(header.first) + L": " + to_hstring(header.second) + L"}\n";
            }

            handler(nullptr, CheckEvent(ping, response.status.code, body, L"", time(nullptr)));
        }
        catch (const std::exception& e)
        {
            handler(nullptr, CheckEvent(0, 0, L"", L"", time(nullptr)));
        }
    }
}
