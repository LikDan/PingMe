#pragma once

#include "RGBA.g.h"
#include "CheckEvent.g.h"

namespace winrt::PingMe::implementation
{
    struct CheckEvent : CheckEventT<CheckEvent>
    {
        CheckEvent(int ping, int statusCode, hstring body, hstring headers, long time)
        {
	        this->ping = ping;
            this->statusCode = statusCode;
            this->body = body;
            this->headers = headers;
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
        hstring Body() { return body; }
        hstring Headers() { return headers; }
        long Time() { return time; }

    private:
        int ping, statusCode;
        hstring body, headers;
        long time;
    };
}

namespace winrt::PingMe::factory_implementation
{
    struct CheckEvent : CheckEventT<CheckEvent, implementation::CheckEvent>
    {
    };
}
