#pragma once

#include "RGBA.g.h"
#include "CheckEvent.g.h"

namespace winrt::PingMe::implementation
{
    struct CheckEvent : CheckEventT<CheckEvent>
    {
        CheckEvent(int ping, int statusCode, long time)
        {
	        this->ping = ping;
	        this->statusCode = statusCode;
            this->time = time;
        };

        RGBA color()
        {
            if (statusCode == 200)
            {
                return RGBA(50, 255, 50);
            }
            if (statusCode == 400)
            {
                return RGBA(255, 50, 50);
            } 

            return RGBA(0, 0, 0, 0);
        }

        int Ping() { return ping; }
        int StatusCode() { return statusCode; }
        long Time() { return time; }

    private:
        int ping, statusCode;
        long time;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct CheckEvent : CheckEventT<CheckEvent, implementation::CheckEvent>
    {
    };
}
