#include "pch.h"
#include "Pinger.h"
#if __has_include("Pinger.g.cpp")
#include "Pinger.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::PingMe::implementation
{
    Pinger::Pinger(hstring host, int timeout, Windows::Foundation::EventHandler<int> const& handler)
    {
        this->timer = DispatcherTimer();
        this->timer.Interval(std::chrono::milliseconds{ timeout });
        this->timer.Start();

        auto lambda = [handler, host](IInspectable const&, IInspectable const&)
        {
            //TODO check site
            handler(nullptr, 1);
        };
        

        this->timer.Tick(lambda);
    }

    void Pinger::Continue()
    {
        //handlerEvent(*this, 1);
    }
}
