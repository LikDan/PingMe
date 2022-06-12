#pragma once

#include "Monitor.g.h"
#include <CheckEvent.g.h>



namespace winrt::PingMe::implementation
{
	struct Monitor : MonitorT<Monitor>
	{
		Monitor(hstring name, hstring host, int timeout, Windows::Foundation::Collections::IVector<winrt::PingMe::CheckEvent> events)
		{
			this->name = name;
			this->host = host;
			this->timeout = timeout;
			this->events = events;
		};

		Monitor()
		{
		};

		void check()
		{
		};

		void start()
		{
		};

		void pause()
		{
		};

		hstring Name() { return this->name; }
		hstring Host() { return this->host; }
		int Timeout() { return this->timeout; }
		Windows::Foundation::Collections::IVector<winrt::PingMe::CheckEvent> Events() { return this->events; }

	private:
		hstring name, host;
		int timeout;

		Windows::Foundation::Collections::IVector<winrt::PingMe::CheckEvent> events;
	};
}

namespace winrt::PingMe::factory_implementation
{
	struct Monitor : MonitorT<Monitor, implementation::Monitor>
	{
	};
}
