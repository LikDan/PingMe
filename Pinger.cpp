#include "pch.h"
#include "Pinger.h"
#if __has_include("Pinger.g.cpp")
#include "Pinger.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    Pinger::Pinger() = default;

    Pinger::Pinger(hstring host, int timeout, Windows::Foundation::EventHandler<PingMe::CheckEvent> const& handler)
    {
        this->handler = handler;
        this->host = host;

        this->timer = DispatcherTimer();
        this->timer.Interval(std::chrono::seconds{ timeout });
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
        //TODO check site

        time_t now = time(nullptr);

        int statusCode = rand() % 500 + 100;
        int ping = rand() % 1000;

        handler(nullptr, CheckEvent(ping, statusCode, now));
    }
}
