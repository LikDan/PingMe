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
            switch (this->statusCode / 100) {
            case 1:
            case 2:
            case 3:
                return RGBA(1, 82, 58);
                break;
            case 0:
            case 4:
            case 5:
                return RGBA(216, 106, 73);
                break;
            default:
                return RGBA(171, 162, 158);
                break;
            }
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
